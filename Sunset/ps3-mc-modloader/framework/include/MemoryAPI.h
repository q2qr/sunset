#pragma once

#include "Types.h"
#include "Syscalls.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int g_targetPid;
void MemoryAPI_Init(void);

#ifdef __cplusplus
}
#endif

template<typename T>
inline bool ReadMemory(uintptr_t address, T* outValue) {
    return ReadProcessMemory(g_targetPid, address, outValue, sizeof(T));
}

template<typename T>
inline T ReadMemoryUnsafe(uintptr_t address) {
    T value;
    ReadProcessMemory(g_targetPid, address, &value, sizeof(T));
    return value;
}

template<typename T>
inline bool WriteMemory(uintptr_t address, const T& value) {
    return WriteProcessMemory(g_targetPid, address, &value, sizeof(T));
}

inline bool WriteByte(uintptr_t address, byte value) {
    return WriteMemory<byte>(address, value);
}

inline bool WriteBytes(uintptr_t address, const byte* bytes, size_t len) {
    return WriteProcessMemory(g_targetPid, address, bytes, len);
}

inline byte ReadByte(uintptr_t address) {
    return ReadMemoryUnsafe<byte>(address);
}
