#include "instruction.h"
#include "cpu.h"

int B(CPU * cpu){
    if (!evaluate_cond((cpu->loadedInstruction >> 28), cpu->registers.cpsr)) return 0;
    
    if (cpu->loadedInstruction & (1 << 26)){
        cpu->registers.LR = cpu->registers.PC + 4;
    }

    int32_t offset = cpu->loadedInstruction & 0x7FFFFF;

    if (cpu->loadedInstruction & 0x800000) {
    // If the sign bit (24th bit) is set, sign-extend the value to 32 bits
    offset |= 0xFF800000;  // Set the upper 8 bits to 1 to make it a negative value
    }
    *cpu->registers.PC += 8;
    return 0;
}



