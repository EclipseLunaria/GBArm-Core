#include "instruction.h"
#include "cpu.h"
#include "registers.h"
#define MRS_INSTR_MASK  0x0FB0FFFF
#define MRS_INSTR_VALUE 0x01000000

// Handles logic for B BL B{cond}
int B(CPU * cpu){

    if (!evaluate_cond((uint8_t)(cpu->loaded_instruction >> 28), cpu->registers.cpsr)) return 0;
    if (cpu->loaded_instruction & (1 << 26)){
        cpu->registers.LR = cpu->registers.PC + 4;
    }

    int32_t offset = cpu->loaded_instruction & 0x7FFFFF;

    if (cpu->loaded_instruction & 0x800000) {
    // If the sign bit (24th bit) is set, sign-extend the value to 32 bits
    offset |= 0xFF800000;  // Set the upper 8 bits to 1 to make it a negative value
    }
    *cpu->registers.PC = offset + 8;
    return 0;
}


int is_mrs(uint32_t instruction){
    return (instruction & MRS_INSTR_MASK) == MRS_INSTR_VALUE;
}

int MRS(instruction_t instruction, CPU* cpu){
    uint8_t ps = (1 << 22) & instruction;
    uint8_t is_privilaged = cpu->registers.current_mode != 0;
    reg_t rd = (instruction >> 12) & 0xF;

    if (ps && is_privilaged){
        write_register(rd, *cpu->registers.current_registers->p_spsr, &cpu->registers);
    }
    else {
        write_register(rd, cpu->registers.cpsr, &cpu->registers);
    }
    return 0;
}