#include "../include/EBOOTHook.h"

static bool g_installed = false;

bool EBOOTHook_Install(void)
{
    g_installed = true;
    return true;
}

void EBOOTHook_Remove(void)
{
    g_installed = false;
}
