#include "branch.h"
#include <stdio.h>

#include "core.h"

int B(instruction_t instruction, CPU *cpu) {
    if ((instruction >> 24) & 1) {
        *cpu->registers.LR = *cpu->registers.PC + 4;
    }

    int32_t offset = (instruction & 0x7FFFFF) * 4;

    if (instruction & 0x800000) {
        // If the sign bit (24th bit) is set, sign-extend the value to 32 bits
        offset |= 0xFF800000;  // Set the upper 8 bits to 1 to make it a
                               // negative value
    }
    *(cpu->registers.PC) += offset + 4;
    return 0;
}
