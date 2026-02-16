#pragma once
#include "Syscalls.h"

extern int g_pid;

template<typename T>
T ReadMemory(uintptr_t address) {
    T value;
    ReadProcessMemory(g_pid, address, &value, sizeof(T));
    return value;
}

template<typename T>
void WriteMemory(uintptr_t address, T value) {
    WriteProcessMemory(g_pid, address, &value, sizeof(T));
}

inline void WriteByte(uintptr_t address, byte value) {
    WriteMemory<byte>(address, value);
}
inline void WriteBytes(uintptr_t address, byte* bytes, size_t len) {
    WriteProcessMemory(g_pid, address, bytes, len);
}
inline byte ReadByte(uintptr_t address) {
    return ReadMemory<byte>(address);
}