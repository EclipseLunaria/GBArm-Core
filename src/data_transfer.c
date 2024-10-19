#include "data_transfer.h"

#include "barrel_shifter.h"
#include "constants.h"
#include "impl_core.h"
#include "registers.h"
#include "types.h"

// Single data transfer
int SDT(instruction_t instruction, CPU *cpu) {
    address_t address = 0;
    BS_FLAGS flags;
    flag_t I = (instruction >> 25) & 1;   // Immediate Offset Flag (0=Immediate, 1=Shifted Register)
    flag_t P = (instruction >> 24) & 1;   // Pre/Post (0=post; add offset after
                                          // transfer, 1=pre; before trans.)
    flag_t U = (instruction >> 23) & 1;   // Up/Down Bit (0=down; subtract offset
                                          // from base, 1=up; add to base)
    flag_t B = (instruction >> 22) & 1;   // Byte/Word bit (0=transfer 32bit/word, 1=transfer 8bit/byte)
    flag_t TW = (instruction >> 21) & 1;  //
    flag_t L = (instruction >> 20) & 1;   // Load/Store bit (0=Store to memory, 1=Load from memory)
    reg_t rn = (instruction >> 16) & 0xF;
    reg_t rd = (instruction >> 12) & 0xF;  // value stored or loaded

    // read register values
    uint32_t rn_value;
    uint32_t rd_value;
    read_register(rn, &cpu->registers, &rn_value);
    read_register(rd, &cpu->registers, &rd_value);

    // handle case of rn or rd == PC
    if (rn == 15) rn_value += 8;
    if (rd == 15) rd_value += 12;

    // calculate offset
    uint32_t offset;
    if (I) {
        offset = instruction & 0xFFF;
    } else {
        uint8_t imm_shift = (instruction >> 7) & 0x4;
        uint8_t shift_type = (instruction >> 5) & 0b11;
        reg_t rm = instruction & 0xF;
        uint32_t rm_value;
        read_register(rm, &cpu->registers, &rm_value);
        offset = imm_shift ? shiftOp[shift_type](imm_shift, rm_value, &flags, &offset) : rm_value;
    }
    address_t offset_address = U ? rn_value + offset : rn_value - offset;
    // set to offset if preindexed
    if (P) address = offset_address;
    if (TW) write_register(rn, address, &cpu->registers);

    if (L) {
        uint32_t value;
        // load from memory
        B ? memory_read_byte(address, &cpu->memory, (byte_t *)&value) : memory_read_word(address, &cpu->memory, &value);
    } else {
        // store to memory
        if (B) rd_value &= 0xFF;
        B ? memory_write_byte(address, (byte_t)rd_value, &cpu->memory)
          : memory_write_word(address, rd_value, &cpu->memory);
    }
    // set address to post index if not already set
    address = offset_address;
    write_register(rn, address, &cpu->registers);
    return 0;
}

int STDT(instruction_t instruction, CPU *cpu) {
    address_t address;
    flag_t P = (instruction >> 24) & 1;   // Pre/Post (0=post; add offset after
                                          // transfer, 1=pre; before trans.)
    flag_t U = (instruction >> 24) & 1;   // Up/Down Bit (0=down; subtract offset
                                          // from base, 1=up; add to base)
    flag_t I = (instruction >> 22) & 1;   // Immediate Offset Flag (0=Immediate, 1=Shifted Register)
    flag_t TW = (instruction >> 21) & 1;  //
    flag_t L = (instruction >> 20) & 1;   // Load/Store bit (0=Store to memory, 1=Load from memory)
    reg_t rn = (instruction >> 16) & 0xF;
    reg_t rd = (instruction >> 12) & 0xF;
    uint8_t opcode = (instruction >> 5) & 0b11;
    uint32_t rn_value;
    uint32_t rd_value;
    read_register(rn, &cpu->registers, &rn_value);
    read_register(rd, &cpu->registers, &rd_value);
    if (rn == 15) rn_value += 8;
    if (rd == 15) rd_value += 12;

    uint32_t offset;
    if (I) {
        offset = (((instruction >> 8) & 0xF) << 4) | (instruction & 0xF);
    } else {
        read_register(instruction & 0xF, &cpu->registers, &offset);
    }

    address = rn_value;
    address_t offset_address = U ? address + offset : address - offset;
    if (P) address = offset_address;
    if (TW) write_register(rn, address, &cpu->registers);
    // Handle operation flow
    if (L) {
        switch (opcode) {
            case 1:
                // load unsigned half word.
                halfword_t value;
                memory_read_halfword(address, &cpu->memory, &value);
                write_register(rd, value, &cpu->registers);
                break;

            case 2:
                // load signed byte.
                byte_t mem_value;
                memory_read_byte(address, &cpu->memory, &mem_value);
                rd_value = (uint32_t)mem_value;
                if (mem_value & 0x80) {      // Check if the 16th bit is set
                                             // (indicating a negative value)
                    rd_value |= 0xFFFFFF00;  // Set the upper 16 bits to 1 for
                                             // sign extension
                } else {
                    rd_value &= 0x000000FF;  // Clear the upper 16 bits (no sign
                                             // extension needed)
                }

                write_register(rd, rd_value, &cpu->registers);
                break;

            case 3:
                // load signed half word.
                halfword_t halfword_value;
                memory_read_halfword(address, &cpu->memory, &halfword_value);
                rd_value = (uint32_t)halfword_value;
                if (rd_value & 0x8000) {
                    rd_value |= 0xFFFF0000;
                } else {
                    rd_value &= 0x0000FFFF;
                }
                write_register(rd, rd_value, &cpu->registers);
                break;

            default:
                break;
        }
    } else {
        switch (opcode) {
            case 1:
                memory_write_halfword(address, rd_value, &cpu->memory);
                break;

            case 2:
                word_t second_register_value;  // rd + 1
                memory_read_word(address, &cpu->memory, &rd_value);
                memory_read_word(address + 4, &cpu->memory, &second_register_value);

                write_register(rd, rd_value, &cpu->registers);
                write_register(rd + 1, second_register_value, &cpu->registers);
                break;

            case 3:
                uint32_t top_register_value;  // rd + 1
                read_register(rd + 1, &cpu->registers, &top_register_value);
                memory_write_word(address, rd_value, &cpu->memory);
                memory_write_word(address + 4, top_register_value, &cpu->memory);
                break;
        }
    }
    address = offset_address;
    return 0;
}
// Block Data Transfer (LDM, STM)
int BDT(instruction_t instruction, CPU *cpu) {
    flag_t P = (instruction >> 24) & 1;
    flag_t U = (instruction >> 23) & 1;
    flag_t S = (instruction >> 22) & 1;
    flag_t W = (instruction >> 21) & 1;
    flag_t L = (instruction >> 20) & 1;
    reg_t rn = (instruction >> 16) & 0xF;

    uint32_t address;
    read_register(rn, &cpu->registers, &address);
    for (int i = 0; i < 16; ++i) {
        if (!((instruction >> i) & 1)) continue;

        if (P) address += U ? 4 : -4;
        uint32_t value;
        if (L) {
            memory_read_word(address, &cpu->memory, &value);
            IS_PRIVILAGED(cpu->registers.current_mode) && S ? write_user_register(i, value, &cpu->registers)
                                                            : write_register(i, value, &cpu->registers);

        } else {
            IS_PRIVILAGED(cpu->registers.current_mode) && S ? read_user_register(i, &cpu->registers, &value)
                                                            : read_register(i, &cpu->registers, &value);
            memory_write_word(address, value, &cpu->memory);
        }
        if (!P) address += U ? 4 : -4;
    }
    if (S && cpu->registers.current_mode != 0) {
        if (L && (instruction >> 15) & 1)
            cpu->registers.cpsr = *cpu->registers.current_registers->p_spsr;
        else if (!L && (instruction >> 15) & 1) {
            *cpu->registers.current_registers->p_spsr = cpu->registers.cpsr;
        }
    }
    if (W) write_register(rn, address, &cpu->registers);
    return 0;
}

int SWP(instruction_t instruction, CPU *cpu) {
    flag_t B = (instruction >> 22) & 1;
    reg_t rn = (instruction >> 16) & 0xF;
    reg_t rd = (instruction >> 12) & 0xF;
    reg_t rm = instruction & 1;
    assert(rn != 15);
    assert(rd != 15);
    assert(rm != 15);

    uint32_t rm_value;
    read_register(rm, &cpu->registers, &rm_value);
    address_t address;
    uint32_t memory_value;
    read_register(rn, &cpu->registers, &address);
    B ? memory_read_byte(address, &cpu->memory, (byte_t *)&memory_value + 3)
      : memory_read_word(address, &cpu->memory, &memory_value);
    B ? memory_write_byte(address, (byte_t)rm_value, &cpu->memory) : memory_write_word(address, rm_value, &cpu->memory);
    write_register(rd, memory_value, &cpu->registers);
    return 0;
}

