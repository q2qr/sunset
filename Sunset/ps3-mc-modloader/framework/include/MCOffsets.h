#pragma once

#include <stdint.h>

namespace MCOffsets {
    static const uintptr_t NoFall          = 0x003A409C;
    static const uintptr_t StopGravity     = 0x00246A2C;
    static const uintptr_t InfiniteBreath  = 0x0039DE28;

    static const uintptr_t GodMode         = 0x004B2021;
    static const uintptr_t DemiGod         = 0x003A4064;
    static const uintptr_t AutoRegen       = 0x002ADCE8;
    static const uintptr_t NoDamageHit     = 0x003A3FF0;

    static const uintptr_t MaxXP           = 0x004B0094;
    static const uintptr_t RemoveXP        = 0x004B00AC;

    static const uintptr_t EnableRain      = 0x00393F8F;
    static const uintptr_t LockWeather     = 0x00393E84;
    static const uintptr_t RemoveWater     = 0x00225E80;

    static const uintptr_t NightVis        = 0x00A9A6C8;
    static const uintptr_t Xray            = 0x00A99154;
    static const uintptr_t NameOverHead1   = 0x00AD8158;
    static const uintptr_t NameOverHead2   = 0x00AD8110;
    static const uintptr_t ChestESP1       = 0x00A98F4C;
    static const uintptr_t ChestESP2       = 0x00A9C2B4;

    static const uintptr_t SuperJump1      = 0x003AA77C;
    static const uintptr_t SuperJump2      = 0x003AA77C;
    static const uintptr_t MultiJump       = 0x0022790B;
    static const uintptr_t MoonGrav        = 0x003ABF88;
    static const uintptr_t WalkInSky       = 0x00011B00;
    static const uintptr_t Speed1          = 0x003ABD49;
    static const uintptr_t Speed2          = 0x003AA999;

    static const uintptr_t AutoSave        = 0x00AEEE54;
    static const uintptr_t InfinitePlace   = 0x0010673F;
    static const uintptr_t NoHurtCam       = 0x00A972B0;
    static const uintptr_t FastBuild       = 0x00AECE70;
    static const uintptr_t InstantMine     = 0x00AEB090;

    // Kagura-derived useful gameplay offsets.
    static const uintptr_t AutoSprint      = 0x00B01DEC;
    static const uintptr_t AutoJump        = 0x00B01BAC;
    static const uintptr_t AlwaysSprint    = 0x00B01EEF;
    static const uintptr_t NoSlowDown      = 0x003AFB60;
    static const uintptr_t NoCollision     = 0x002271B0;
    static const uintptr_t CanFly          = 0x00B02378;
    static const uintptr_t DisablePortals  = 0x002379E7;
    static const uintptr_t InstantHit      = 0x00AEBED4;
    static const uintptr_t AutoHit         = 0x00AEC34C;
    static const uintptr_t ReachAttackA    = 0x00A95FB9;
    static const uintptr_t ReachAttackB    = 0x00A95FC1;
    static const uintptr_t KillAura        = 0x00233290;
    static const uintptr_t FreeCam         = 0x00A98A95;
    static const uintptr_t OptimizeChunks  = 0x00B21C60;
    static const uintptr_t WallHack        = 0x00A98F50;

    // Kagura-derived UI/render offsets.
    static const uintptr_t ButtonMonitoring    = 0x3000CF79;
    static const uintptr_t GuiFillRect         = 0x00A7CE80;
    static const uintptr_t GuiDrawString       = 0x00A7E5DC;
    static const uintptr_t DrawShadowText      = 0x00A7E2E8;
    static const uintptr_t ConsoleUIController = 0x01558228;
    static const uintptr_t PlayUISFX           = 0x00886798;
    static const uintptr_t SoundEventBack      = 0x014CA684;
    static const uintptr_t SoundEventCraft     = 0x014CA688;
    static const uintptr_t SoundEventFocus     = 0x014CA690;
    static const uintptr_t SoundEventPress     = 0x014CA694;
    static const uintptr_t SoundEventScroll    = 0x014CA698;
    static const uintptr_t CInputObject        = 0x016BD748;
    static const uintptr_t RequestKeyboardFn   = 0x00C62B80;
}

