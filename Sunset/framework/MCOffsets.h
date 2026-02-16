#pragma once
#include <stdint.h>

namespace MCOffsets {
    // movement
    constexpr uintptr_t NoFall          = 0x003A409C;
    constexpr uintptr_t StopGravity     = 0x00246A2C;
    constexpr uintptr_t InfiniteBreath  = 0x0039DE28;

    // health
    constexpr uintptr_t GodMode         = 0x004B2021;
    constexpr uintptr_t DemiGod         = 0x003A4064;
    constexpr uintptr_t AutoRegen       = 0x002ADCE8;
    constexpr uintptr_t NoDamageHit     = 0x003A3FF0;

    // xp
    constexpr uintptr_t MaxXP           = 0x004B0094;
    constexpr uintptr_t RemoveXP        = 0x004B00AC;

    // world
    constexpr uintptr_t EnableRain      = 0x00393F8F;
    constexpr uintptr_t LockWeather     = 0x00393E84;
    constexpr uintptr_t RemoveWater     = 0x00225E80;

    // visual (non-host)
    constexpr uintptr_t NightVis        = 0x00A9A6C8;
    constexpr uintptr_t Xray            = 0x00A99154;
    constexpr uintptr_t NameOverHead1   = 0x00AD8158;
    constexpr uintptr_t NameOverHead2   = 0x00AD8110;
    constexpr uintptr_t ChestESP1       = 0x00A98F4C;
    constexpr uintptr_t ChestESP2       = 0x00A9C2B4;

    // movement (non-host)
    constexpr uintptr_t SuperJump1      = 0x003AA77C;
    constexpr uintptr_t SuperJump2      = 0x003AA77C;
    constexpr uintptr_t MultiJump       = 0x0022790B;
    constexpr uintptr_t MoonGrav        = 0x003ABF88;
    constexpr uintptr_t WalkInSky       = 0x00011B00;
    constexpr uintptr_t Speed1          = 0x003ABD49;
    constexpr uintptr_t Speed2          = 0x003AA999;

    // misc
    constexpr uintptr_t AutoSave        = 0x00AEEE54;
    constexpr uintptr_t InfinitePlace   = 0x0010673F;
    constexpr uintptr_t NoHurtCam       = 0x00A972B0;
    constexpr uintptr_t FastBuild       = 0x00AECE70;
    constexpr uintptr_t InstantMine     = 0x00AEB090;
}