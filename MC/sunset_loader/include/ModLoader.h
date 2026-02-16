#pragma once

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

void ModLoader_Init(void);
void ModLoader_Tick(void);
void ModLoader_Shutdown(void);
int ModLoader_LoadedCount(void);
int ModLoader_GetLoadedMods(ModPublicInfo* outMods, int maxCount);

#ifdef __cplusplus
}
#endif
