#include "multiply.h"

// Multiply and Multiply-Accumulate (MUL, MLA)
int handleMultiply(uint32_t instruction, CPU* cpu){
    uint8_t A = (instruction >> 21) & 1;
    uint8_t S = (instruction >> 20) & 1;
    uint8_t rd = (instruction >> 16) & 0xF;
    uint8_t rn = (instruction >> 12) & 0xF;
    uint8_t rs = (instruction >> 8) & 0xF;
    uint8_t rm = instruction & 0xF;

    // register values
    uint32_t rmValue;
    uint32_t rsValue;
    uint32_t rnValue;
    readRegister(rm, &cpu->registers, &rmValue);
    readRegister(rs, &cpu->registers, &rsValue);
    readRegister(rn, &cpu->registers, &rnValue);

    
    uint32_t rdValue = rmValue * rsValue;
    if (A) rdValue += rnValue;

    writeRegister(rd, rdValue, &cpu->registers);
    if (S) {
        cpu->CPSR->Z = rdValue == 0;
        cpu->CPSR->N = (rdValue >> 31) & 1;
    }

    return 0;
}

int handleLongMultiply(uint32_t instruction, CPU* cpu){
    // extract flags
    flag_t U = (instruction >> 22) & 1;
    flag_t A = (instruction >> 21) & 1;
    flag_t S = (instruction >> 20) & 1;

    // get destination hi/lo registers
    reg_t rdh = (instruction >> 16) & 0xF;
    reg_t rdl = (instruction >> 12) & 0xF;
    uint32_t rdlValue;
    uint32_t rdhValue;
    readRegister(rdh, &cpu->registers, &rdhValue);
    readRegister(rdl, &cpu->registers, &rdlValue);

    // get operand registers
    reg_t rs = (instruction >> 8) & 0xF;
    reg_t rm = instruction & 0xF;
    uint32_t rsValue;
    uint32_t rmValue;
    readRegister(rs, &cpu->registers, &rsValue);
    readRegister(rm, &cpu->registers, &rmValue);

    uint64_t product = rsValue * rmValue;
}