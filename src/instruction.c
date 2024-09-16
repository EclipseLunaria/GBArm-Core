#include "instruction.h"
#include "cpu.h"
#include "registers.h"
#include "constants.h"
#include "barrel_shifter.h"

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
    uint8_t ps = (instruction >> 22) & 1;
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

#define MSR_REG_MASK_VALUE 0x0FC00000  // Mask for bits [27:22]
#define MSR_REG_VALUE      0x01000000  // Value for bits [27:22] = '000100'

int is_msr_reg(instruction_t instruction) {
    return (instruction & MSR_REG_MASK_VALUE) == MSR_REG_VALUE;
}

// TODO: Combine MSR functions.
int MSR_REG(instruction_t instruction, CPU * cpu){
    flag_t f = (instruction >> 19) & 1;
    flag_t c = (instruction >> 16) & 1;
    reg_t rm = instruction & 0xF;
    uint32_t rm_value;
    read_register(rm, cpu, &rm_value);

    if (cpu->registers.current_mode != USER_MODE && c){
        //clear flags
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
#define MSR_IMM_VALUE      0x03200000  // Value for MSR (immediate)

int is_msr_imm(instruction_t instruction){
    return (instruction & MSR_IMM_MASK_VALUE) == MSR_IMM_VALUE;
}

int MSR_IMM(instruction_t instruction, CPU*cpu){
    flag_t f = (instruction >> 19) & 1;
    flag_t c = (instruction >> 16) & 1;
    uint32_t imm = instruction & 0x0000000F;
    uint32_t shift = instruction & 0x00000400;
    BS_FLAGS flags;
    uint32_t result;

    BS_ROR(imm, shift, &flags, &result);
        if (cpu->registers.current_mode != USER_MODE && c){
        //clear flags
        cpu->registers.cpsr &= 0xFFFFFFF0;
        cpu->registers.cpsr |= result & 0xF;
    }
    if (f) {
        cpu->registers.cpsr = 0x0FFFFFFFF;
        cpu->registers.cpsr |= result & 0xF0000000;
    }
    return 0;
}

// Single data transfer
int SDT(instruction_t instruction, CPU *cpu){
    address_t address;
    BS_FLAGS flags;
    flag_t I = (instruction >> 25) & 1; // Immediate Offset Flag (0=Immediate, 1=Shifted Register)
    flag_t P = (instruction >> 24) & 1; // Pre/Post (0=post; add offset after transfer, 1=pre; before trans.)
    flag_t U = (instruction >> 24) & 1; // Up/Down Bit (0=down; subtract offset from base, 1=up; add to base)
    flag_t B = (instruction >> 22) & 1; // Byte/Word bit (0=transfer 32bit/word, 1=transfer 8bit/byte)
    flag_t TW = (instruction >> 21) & 1;// 
    flag_t L = (instruction >> 20) & 1; // Load/Store bit (0=Store to memory, 1=Load from memory)
    reg_t rn = (instruction >> 16) & 0xF;
    reg_t rd = (instruction >> 12) & 0xF;
    uint32_t rn_value;
    uint32_t rd_value;
    read_register(rn, cpu, &rn_value);
    read_register(rd, cpu, &rd_value);
    if (rn == 15) rn_value += 8;
    if (rd == 15) rd_value += 12;

    // calculate offset
    int offset;
    if (I) offset = instruction & 0xFFF;
    else {
        uint8_t imm_shift = (instruction >> 7) & 0x4;
        uint8_t shift_type = (instruction >> 5) & 0b11;
        reg_t rm = instruction & 0xF;
        uint32_t rm_value;
        read_register(rm, &cpu->registers, rm_value);
        offset = shiftOp[shift_type](imm_shift, rm_value,&flags,&offset);
    }
    address_t offset_address = U ? rn_value + offset : rn_value - offset;
    //set to offset if preindexed
    if (P) address = offset_address;
    if(TW) write_register(rn, address,&cpu->registers);

    if (L){
        uint32_t value;
        // load from memory
        B ? read_byte(address, &value) : read_word(address, &value);
    }
    else {
        //store to memory
        if (B) rd_value &= 0xFF;
        B ? write_byte(address, rd_value): write_word(address, &rd_value);
    }
    // set address to post index if not already set
    address = offset_address;
    return 0;

}

int store_half_word(address_t address, reg_t rd, word_t word, CPU* cpu){
    write_half_word(address, (uint16_t)word);
}

int load_double_word(address_t address, reg_t rd, word_t word, CPU *cpu){

}


int STDT(instruction_t instruction, CPU *cpu){
    address_t address;
    BS_FLAGS flags;
    flag_t P = (instruction >> 24) & 1; // Pre/Post (0=post; add offset after transfer, 1=pre; before trans.)
    flag_t U = (instruction >> 24) & 1; // Up/Down Bit (0=down; subtract offset from base, 1=up; add to base)
    flag_t I = (instruction >> 22) & 1; // Immediate Offset Flag (0=Immediate, 1=Shifted Register)
    flag_t TW = (instruction >> 21) & 1;// 
    flag_t L = (instruction >> 20) & 1; // Load/Store bit (0=Store to memory, 1=Load from memory)
    reg_t rn = (instruction >> 16) & 0xF;
    reg_t rd = (instruction >> 12) & 0xF;
    uint8_t opcode = (instruction >> 5) & 0b11;
    uint32_t rn_value;
    uint32_t rd_value;
    read_register(rn, cpu, &rn_value);
    read_register(rd, cpu, &rd_value);
    if (rn == 15) rn_value += 8;
    if (rd == 15) rd_value += 12;

    uint32_t offset;
    if (I) {
        offset = (((instruction >> 8) & 0xF ) << 4) | (instruction  & 0xF);
    }
    else {
        read_register(instruction & 0xF, &cpu->registers, &offset);
    }
    address = rn_value;
    address_t offset_address = U ? address + offset : address - offset;


}
