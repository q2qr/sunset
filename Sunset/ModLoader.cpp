#include "ModLoader.h"
#include "Filesystem.h"
#include <sys/prx.h>
#include <cell/cell_fs.h>
#include <string.h>
#include <stdio.h>

#define MAX_MODS 32

static LoadedMod g_mods[MAX_MODS];
static int g_modCount = 0;
int g_pid = 0;

void ModLoader_Init() {
    g_pid = GetCurrentPid();

    char modPath[256];
    snprintf(modPath, sizeof(modPath),
        "/dev_hdd0/tmp/sunsetml/mods/");

    ScanAndLoadMods(modPath);
}

void ModLoader_Tick() {
    for (int i = 0; i < g_modCount; i++) {
        if (g_mods[i].active && g_mods[i].info->onTick) {
            g_mods[i].info->onTick();
        }
    }
}

void ModLoader_Shutdown() {
    for (int i = 0; i < g_modCount; i++) {
        if (g_mods[i].active) {
            if (g_mods[i].info->onUnload)
                g_mods[i].info->onUnload();
            sys_prx_stop_module(g_mods[i].prxId, 0, NULL, NULL, 0, NULL);
            sys_prx_unload_module(g_mods[i].prxId, 0, NULL);
        }
    }
    g_modCount = 0;
}

static void LoadMod(const char* path) {
    if (g_modCount >= MAX_MODS) return;

    sys_prx_id_t id = sys_prx_load_module(path, 0, NULL);
    if (id < 0) return;

    int ret;
    sys_prx_start_module(id, 0, NULL, &ret, 0, NULL);

    // mod exports a symbol "ModInfo"
    sys_prx_module_info_t info;
    sys_prx_get_module_info(id, &info);

    Mod* mod = (Mod*)info.segments[0].base; // simplified
    if (!mod) return;

    g_mods[g_modCount++] = { id, mod, true };

    if (mod->onLoad)
        mod->onLoad();
}

void ScanAndLoadMods(const char* path) {
    int fd;
    if (cellFsOpendir(path, &fd) != CELL_FS_SUCCEEDED) return;

    CellFsDirent entry;
    uint64_t nread;

    while (cellFsReaddir(fd, &entry, &nread) == CELL_FS_SUCCEEDED
        && nread > 0) {
        if (entry.d_name[0] == '.') continue;

        char* ext = strrchr(entry.d_name, '.');
        if (!ext || strcmp(ext, ".sprx") != 0) continue;

        char fullPath[256];
        snprintf(fullPath, sizeof(fullPath), "%s%s", path, entry.d_name);
        LoadMod(fullPath);
    }

    cellFsClosedir(fd);
}