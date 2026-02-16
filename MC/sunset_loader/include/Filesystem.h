#pragma once

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

int EnumerateModEntries(const char* modPath, char outPaths[][256], int maxCount);
bool ExtractSunsetPackage(const char* packagePath, char* outSprxPath, size_t outSprxPathSize, ModPublicInfo* outInfo);

#ifdef __cplusplus
}
#endif
