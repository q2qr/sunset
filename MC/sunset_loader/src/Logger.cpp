#include "../include/Logger.h"

extern "C" void Logger_Init(void)
{
}

extern "C" void Logger_Shutdown(void)
{
}

extern "C" void Logger_Logf(const char* fmt, ...)
{
    (void)fmt;
}