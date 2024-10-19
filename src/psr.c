#include "psr.h"
#include "registers.h"
#include "impl_core.h"
#include "barrel_shifter.h"

#define MRS_INSTR_MASK 0x0FB0FFFF
#define MRS_INSTR_VALUE 0x01000000

int is_mrs(uint32_t instruction) { return (instruction & MRS_INSTR_MASK) == MRS_INSTR_VALUE; }

int MRS(instruction_t instruction, CPU *cpu) {
    uint8_t ps = (instruction >> 22) & 1;
    uint8_t is_privilaged = cpu->registers.current_mode != 0;
    reg_t rd = (instruction >> 12) & 0xF;
    if (ps && is_privilaged) {
        write_register(rd, *cpu->registers.current_registers->p_spsr, &cpu->registers);
    } else {
        write_register(rd, cpu->registers.cpsr, &cpu->registers);
    }
    return 0;
}

#define MSR_REG_MASK_VALUE 0x0FC00000  // Mask for bits [27:22]
#define MSR_REG_VALUE 0x01000000       // Value for bits [27:22] = '000100'

int is_msr_reg(instruction_t instruction) { return (instruction & MSR_REG_MASK_VALUE) == MSR_REG_VALUE; }

// TODO: Combine MSR functions.
int MSR_REG(instruction_t instruction, CPU *cpu) {
    flag_t f = (instruction >> 19) & 1;
    flag_t c = (instruction >> 16) & 1;
    reg_t rm = instruction & 0xF;
    uint32_t rm_value;
    read_register(rm, &cpu->registers, &rm_value);

    if (cpu->registers.current_mode != USER_MODE && c) {
        // clear flags
        cpu->registers.cpsr &= 0xFFFFFFF0;
        cpu->registers.cpsr |= rm_value & 0xF;
    }
    if (f) {
        cpu->registers.cpsr = 0x0FFFFFFFF;
        cpu->registers.cpsr |= rm_value & 0xF0000000;
    }

    return 0;
}

#define MSR_IMM_MASK_VALUE 0x0FB00000  // Mask for MSR (immediate)
#define MSR_IMM_VALUE 0x03200000       // Value for MSR (immediate)

int is_msr_imm(instruction_t instruction) { return (instruction & MSR_IMM_MASK_VALUE) == MSR_IMM_VALUE; }

int MSR_IMM(instruction_t instruction, CPU *cpu) {
    flag_t f = (instruction >> 19) & 1;
    flag_t c = (instruction >> 16) & 1;
    uint32_t imm = instruction & 0x0000000F;
    uint32_t shift = instruction & 0x00000400;
    BS_FLAGS flags;
    uint32_t result;

    BS_ROR(imm, shift, &flags, &result);
    if (cpu->registers.current_mode != USER_MODE && c) {
        // clear flags
        cpu->registers.cpsr &= 0xFFFFFFF0;
        cpu->registers.cpsr |= result & 0xF;
    }
    if (f) {
        cpu->registers.cpsr = 0x0FFFFFFFF;
        cpu->registers.cpsr |= result & 0xF0000000;
    }
    return 0;
}


