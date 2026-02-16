#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void Logger_Init(void);
void Logger_Shutdown(void);
void Logger_Logf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif
