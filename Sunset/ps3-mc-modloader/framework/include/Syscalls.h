#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t Syscall(int id, ...);
uint64_t CobraCall(int id, ...);
int GetCurrentPid(void);
bool ReadProcessMemory(int pid, uintptr_t address, void* data, size_t len);
bool WriteProcessMemory(int pid, uintptr_t address, const void* data, size_t len);

#ifdef __cplusplus
}
#endif
