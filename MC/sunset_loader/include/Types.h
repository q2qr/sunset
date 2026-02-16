#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/prx.h>

typedef unsigned char byte;
typedef unsigned int uint;

typedef struct Mod {
    const char* name;
    const char* author;
    const char* version;
    void (*onLoad)(void);
    void (*onUnload)(void);
    void (*onTick)(void);
} Mod;

typedef struct ModPublicInfo {
    char name[64];
    char author[64];
    char version[32];
    char description[128];
    char packagePath[256];
    char sprxPath[256];
    char previewImagePath[256];
    bool active;
    bool fromSunsetPackage;
} ModPublicInfo;

typedef struct LoadedMod {
    sys_prx_id_t prxId;
    Mod* info;
    bool active;
    char path[256];
    ModPublicInfo publicInfo;
} LoadedMod;
