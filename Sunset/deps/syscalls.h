#pragma once
#include <stdint.h>


uint64_t Syscall(int id, ...);
uint64_t CobraCall(int id, ...);

int GetCurrentPid();

bool ReadProcessMemory(int pid, uintptr_t address, void* data, size_t len);

bool WriteProcessMemory(int pid, uintptr_t address, void* data, size_t len);