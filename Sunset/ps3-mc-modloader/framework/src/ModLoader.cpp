#include "../include/ModLoader.h"
#include "../include/Filesystem.h"
#include "../include/MemoryAPI.h"

#include <stdio.h>
#include <string.h>
#include <sys/prx.h>

#define MAX_MODS 32
#ifndef MODLOADER_TITLE_ID
#define MODLOADER_TITLE_ID "NPUB31419"
#endif

static LoadedMod g_mods[MAX_MODS];
static int g_modCount = 0;

static void SafeCopy(char* dst, size_t dstSize, const char* src)
{
    if (!dst || dstSize == 0) {
        return;
    }
    if (!src) {
        dst[0] = '\0';
        return;
    }
    strncpy(dst, src, dstSize - 1);
    dst[dstSize - 1] = '\0';
}

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

static Mod* ResolveModInfo(sys_prx_id_t id)
{
    sys_prx_module_info_t modInfo;
    memset(&modInfo, 0, sizeof(modInfo));
    modInfo.size = sizeof(modInfo);
    if (sys_prx_get_module_info(id, 0, &modInfo) < 0) {
        return 0;
    }

    if (modInfo.segments_num == 0 || modInfo.segments[0].base == 0) {
        return 0;
    }

    return (Mod*)modInfo.segments[0].base;
}

static void PopulateMetadataFromMod(ModPublicInfo* outInfo, const Mod* mod)
{
    if (!outInfo || !mod) {
        return;
    }

    if (outInfo->name[0] == '\0') {
        SafeCopy(outInfo->name, sizeof(outInfo->name), mod->name);
    }
    if (outInfo->author[0] == '\0') {
        SafeCopy(outInfo->author, sizeof(outInfo->author), mod->author);
    }
    if (outInfo->version[0] == '\0') {
        SafeCopy(outInfo->version, sizeof(outInfo->version), mod->version);
    }
}

static bool LoadModAtPath(const char* path)
{
    if (g_modCount >= MAX_MODS) {
        return false;
    }

    char loadPath[256];
    SafeCopy(loadPath, sizeof(loadPath), path);

    ModPublicInfo packageInfo;
    memset(&packageInfo, 0, sizeof(packageInfo));
    SafeCopy(packageInfo.packagePath, sizeof(packageInfo.packagePath), path);
    packageInfo.fromSunsetPackage = EndsWith(path, ".sunset");

    if (packageInfo.fromSunsetPackage) {
        if (!ExtractSunsetPackage(path, loadPath, sizeof(loadPath), &packageInfo)) {
            return false;
        }
    } else {
        SafeCopy(packageInfo.sprxPath, sizeof(packageInfo.sprxPath), path);
    }

    sys_prx_id_t id = sys_prx_load_module(loadPath, 0, 0);
    if (id < 0) {
        return false;
    }

    int startResult = 0;
    if (sys_prx_start_module(id, 0, 0, &startResult, 0, 0) < 0) {
        sys_prx_unload_module(id, 0, 0);
        return false;
    }

    Mod* modInfo = ResolveModInfo(id);
    if (modInfo == 0) {
        sys_prx_stop_module(id, 0, 0, 0, 0, 0);
        sys_prx_unload_module(id, 0, 0);
        return false;
    }

    LoadedMod* slot = &g_mods[g_modCount++];
    memset(slot, 0, sizeof(*slot));

    slot->prxId = id;
    slot->info = modInfo;
    slot->active = true;
    SafeCopy(slot->path, sizeof(slot->path), path);
    slot->publicInfo = packageInfo;
    slot->publicInfo.active = true;
    PopulateMetadataFromMod(&slot->publicInfo, modInfo);

    if (modInfo->onLoad) {
        modInfo->onLoad();
    }

    return true;
}

void ModLoader_Init(void)
{
    MemoryAPI_Init();

    const char* modPath = "/dev_hdd0/tmp/sunsetml/mods/";

    char paths[MAX_MODS][256];
    int count = EnumerateModEntries(modPath, paths, MAX_MODS);
    for (int i = 0; i < count; ++i) {
        LoadModAtPath(paths[i]);
    }
}

void ModLoader_Tick(void)
{
    for (int i = 0; i < g_modCount; ++i) {
        if (g_mods[i].active && g_mods[i].info && g_mods[i].info->onTick) {
            g_mods[i].info->onTick();
        }
    }
}

void ModLoader_Shutdown(void)
{
    for (int i = 0; i < g_modCount; ++i) {
        if (!g_mods[i].active) {
            continue;
        }

        if (g_mods[i].info && g_mods[i].info->onUnload) {
            g_mods[i].info->onUnload();
        }

        sys_prx_stop_module(g_mods[i].prxId, 0, 0, 0, 0, 0);
        sys_prx_unload_module(g_mods[i].prxId, 0, 0);
        g_mods[i].active = false;
        g_mods[i].publicInfo.active = false;
    }

    g_modCount = 0;
}

int ModLoader_LoadedCount(void)
{
    return g_modCount;
}

int ModLoader_GetLoadedMods(ModPublicInfo* outMods, int maxCount)
{
    if (!outMods || maxCount <= 0) {
        return 0;
    }

    int copied = 0;
    for (int i = 0; i < g_modCount && copied < maxCount; ++i) {
        if (!g_mods[i].active) {
            continue;
        }
        outMods[copied++] = g_mods[i].publicInfo;
    }

    return copied;
}
