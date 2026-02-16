#include "../include/MemoryAPI.h"

int g_targetPid = 0;

void MemoryAPI_Init(void)
{
    g_targetPid = GetCurrentPid();
}
