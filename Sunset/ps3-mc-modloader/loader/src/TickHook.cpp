#include "../include/TickHook.h"

static void (*g_tickCallback)(void) = 0;
static bool g_tickHookInstalled = false;

bool TickHook_Install(void (*tickCallback)(void))
{
    g_tickCallback = tickCallback;
    g_tickHookInstalled = (tickCallback != 0);
    return g_tickHookInstalled;
}

void TickHook_Remove(void)
{
    g_tickHookInstalled = false;
    g_tickCallback = 0;
}

void TickHook_RunManualTick(void)
{
    if (g_tickHookInstalled && g_tickCallback) {
        g_tickCallback();
    }
}
