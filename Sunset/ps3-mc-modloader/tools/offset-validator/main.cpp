#include <stdio.h>
#include "../../framework/include/MCOffsets.h"

int main()
{
    struct OffsetEntry {
        const char* name;
        uintptr_t value;
    } entries[] = {
        {"NoFall", MCOffsets::NoFall},
        {"AutoRegen", MCOffsets::AutoRegen},
        {"GodMode", MCOffsets::GodMode},
        {"Xray", MCOffsets::Xray},
    };

    int failed = 0;
    for (size_t i = 0; i < sizeof(entries) / sizeof(entries[0]); ++i) {
        printf("%-12s : 0x%08X\n", entries[i].name, (unsigned int)entries[i].value);
        if (entries[i].value == 0) {
            ++failed;
        }
    }

    if (failed > 0) {
        printf("Invalid offsets: %d\n", failed);
        return 1;
    }

    printf("All checked offsets are non-zero.\n");
    return 0;
}
