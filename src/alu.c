#include "alu.h"



int ALU_AND(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}

int ALU_EOR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 ^ op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;

}

int ALU_SUB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    
    *result = op1 - op2;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}

int ALU_RSB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2 - op1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op2_sign != result_sign);
    return 0;
}

int ALU_ADD(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 + op2;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_ADC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
        *result = op1 + op2 + flags->C;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_SBC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 - op2 + flags->C - 1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}

int ALU_RSC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2 - op1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op2_sign != result_sign);
    return 0;
}

int ALU_TST(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}
int ALU_TEQ(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 ^ op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}
int ALU_CMP(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 - op2;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}
int ALU_CMN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 + op2;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_ORR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 | op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_MOV(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_BIC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & ~op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_MVN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = ~op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}

int (*aluOp[16])(uint32_t, uint32_t, BS_FLAGS*, uint32_t*) = {
    ALU_AND,
    ALU_EOR,
    ALU_SUB,
    ALU_RSB,
    ALU_ADD,
    ALU_ADC,
    ALU_SBC,
    ALU_RSC,
    ALU_TST,
    ALU_TEQ,
    ALU_CMP,
    ALU_CMN,
    ALU_ORR,
    ALU_MOV,
    ALU_BIC,
    ALU_MVN
};


uint32_t ALU_ROR(uint32_t value, uint8_t shiftAmt, CPU* cpu){
    shiftAmt %= 32;
    return (value >> shiftAmt) | (value << (32 - shiftAmt));
}



// REFERENCE (4-12): https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf
int ALUExecute(uint32_t instruction, CPU *cpu) {
    BS_FLAGS flags;
    uint8_t rn = (instruction >> 16) & 0xF;
    uint8_t rd = (instruction >> 12) & 0xF;
    uint8_t opcode = (instruction >> 21) & 0xF;
    uint8_t writableOperation = (opcode >> 2) != 0x3;
    uint32_t op2;
    uint8_t I = (instruction >> 25) & 1;
    uint8_t S = (instruction >> 20) & 1;
    
    // evaluate op2
    if (I){
        // if immediate flag set
        uint8_t rotate = instruction >> 8 & 0xF;
        uint32_t imm = instruction & 0xFF;
        BS_ROR(imm, 2*rotate, &flags, &op2);
    }
    else {
        uint32_t shiftAmt;
        uint32_t rm;
        readRegister(instruction & 0xF, &cpu->registers, &rm);
        if ((instruction >> 4 & 1)){
            //Shift by register at bit 8-11
            readRegister((instruction >> 8) & 0xF, &cpu->registers, &shiftAmt);
            shiftAmt &= 0xF;
        }
        else {
            shiftAmt = (instruction >> 7) & 0x1F; 
        }
        shiftOp[(instruction >> 5) & 0b11](rm, shiftAmt, &flags, &op2);
    }
    //evaluate expression
    uint32_t regOut;
    aluOp[opcode](rn, op2,&flags,&regOut);
    
    if (writableOperation){
        // valid write operation
        writeRegister(rd, regOut, &cpu->registers);
    }

    if (S) {
        cpu->CPSR->C = flags.C;
        cpu->CPSR->N = flags.N;
        cpu->CPSR->Z = flags.Z;
        if (flags.IsArithmetic) cpu->CPSR->V = flags.V;

    }

    return 0;
}