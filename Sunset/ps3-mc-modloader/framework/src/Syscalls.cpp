#include "../include/Syscalls.h"

__attribute__((naked, noinline)) uint64_t Syscall(int id, ...)
{
    asm(
        ".set STACK_SIZE, 0x70;"
        ".set LINK_REGISTER, 0x10;"
        "mflr %r0;"
        "std %r0, LINK_REGISTER(%r1);"
        "stdu %r1, -STACK_SIZE(%r1);"
        "mr %r11, %r3;"
        "mr %r3, %r4;"
        "mr %r4, %r5;"
        "mr %r5, %r6;"
        "mr %r6, %r7;"
        "mr %r7, %r8;"
        "mr %r8, %r9;"
        "mr %r9, %r10;"
        "sc;"
        "addi %r1, %r1, STACK_SIZE;"
        "ld %r0, LINK_REGISTER(%r1);"
        "mtlr %r0;"
        "blr;");
    return __reg(3);
}

__attribute__((naked, noinline)) uint64_t CobraCall(int id, ...)
{
    asm(
        ".set STACK_SIZE, 0x70;"
        ".set LINK_REGISTER, 0x10;"
        "mflr %r0;"
        "std %r0, LINK_REGISTER(%r1);"
        "stdu %r1, -STACK_SIZE(%r1);"
        "li %r11, 8;"
        "sc;"
        "addi %r1, %r1, STACK_SIZE;"
        "ld %r0, LINK_REGISTER(%r1);"
        "mtlr %r0;"
        "blr;");
    return __reg(3);
}

int GetCurrentPid(void)
{
    return (int)Syscall(1);
}

bool ReadProcessMemory(int pid, uintptr_t address, void* data, size_t len)
{
    return CobraCall(0x7777, 0x31, pid, address, data, len) == 0;
}

bool WriteProcessMemory(int pid, uintptr_t address, const void* data, size_t len)
{
    return CobraCall(0x7777, 0x32, pid, address, data, len) == 0;
}
