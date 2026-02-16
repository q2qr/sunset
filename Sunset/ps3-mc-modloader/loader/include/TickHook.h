#pragma once

#ifdef __cplusplus
extern "C" {
#endif

bool TickHook_Install(void (*tickCallback)(void));
void TickHook_Remove(void);
void TickHook_RunManualTick(void);

#ifdef __cplusplus
}
#endif
