#include "../include/ModLoader.h"

#include <cell/cell_fs.h>
#include <string.h>
#include <sys/prx.h>

#define MAX_MODS 32

static sys_prx_id_t g_loadedMods[MAX_MODS];
static int g_loadedCount = 0;

static bool EndsWith(const char* value, const char* suffix)
{
    if (!value || !suffix) {
        return false;
    }

    size_t valueLen = strlen(value);
    size_t suffixLen = strlen(suffix);
    if (suffixLen > valueLen) {
        return false;
    }

    return strcmp(value + (valueLen - suffixLen), suffix) == 0;
}

static bool TryLoadModule(const char* path)
{
    if (!path || g_loadedCount >= MAX_MODS) {
        return false;
    }

    sys_prx_id_t id = sys_prx_load_module(path, 0, 0);
    if (id < 0) {
        return false;
    }

    int startResult = 0;
    int startRc = sys_prx_start_module(id, 0, 0, &startResult, 0, 0);
    if (startRc < 0) {
        sys_prx_unload_module(id, 0, 0);
        return false;
    }

    g_loadedMods[g_loadedCount++] = id;
    return true;
}

void ModLoader_Init(void)
{
    g_loadedCount = 0;
    const char* modPath = "/dev_hdd0/tmp/sunsetml/mods/";
    int dirFd = -1;
    if (cellFsOpendir(modPath, &dirFd) != CELL_FS_SUCCEEDED) {
        return;
    }

    CellFsDirent entry;
    uint64_t nread = 0;
    while (g_loadedCount < MAX_MODS &&
           cellFsReaddir(dirFd, &entry, &nread) == CELL_FS_SUCCEEDED &&
           nread > 0) {
        if (entry.d_name[0] == '.') {
            continue;
        }
        if (!EndsWith(entry.d_name, ".sprx")) {
            continue;
        }

        char fullPath[256];
        fullPath[0] = '\0';
        strncat(fullPath, modPath, sizeof(fullPath) - 1);
        strncat(fullPath, entry.d_name, sizeof(fullPath) - strlen(fullPath) - 1);

        TryLoadModule(fullPath);
    }

    cellFsClosedir(dirFd);
}

void ModLoader_Tick(void)
{
}

void ModLoader_Shutdown(void)
{
    for (int i = 0; i < g_loadedCount; ++i) {
        sys_prx_stop_module(g_loadedMods[i], 0, 0, 0, 0, 0);
        sys_prx_unload_module(g_loadedMods[i], 0, 0);
    }
    g_loadedCount = 0;
}

int ModLoader_LoadedCount(void)
{
    return g_loadedCount;
}

int ModLoader_GetLoadedMods(ModPublicInfo* outMods, int maxCount)
{
    (void)outMods;
    (void)maxCount;
    return 0;
}