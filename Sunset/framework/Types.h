#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef unsigned char byte;
typedef unsigned int uint;

// every mod must fill this out
struct Mod {
    const char* name;
    const char* author;
    const char* version;
    void (*onLoad)();
    void (*onUnload)();
    void (*onTick)();
};

struct LoadedMod {
    sys_prx_id_t prxId;
    Mod* info;
    bool active;
};