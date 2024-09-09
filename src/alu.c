#include "alu.h"



uint32_t ALU_AND(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_EOR(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 ^ op2;
}

uint32_t ALU_SUB(uint32_t op1, uint32_t op2, CPU* cpu){
    if (op1 < op2) cpu->CPSR->N = 1;
    return op1 - op2;
}

uint32_t ALU_RSB(uint32_t op1, uint32_t op2, CPU* cpu){
    return op2 - op1;
}

uint32_t ALU_ADD(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 + op2;
}

uint32_t ALU_ADC(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 + op2 + cpu->CPSR->C;
}

uint32_t ALU_SBC(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_RSC(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_TST(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_TEQ(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_CMP(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_CMN(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & op2;
}

uint32_t ALU_ORR(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 | op2;
}

uint32_t ALU_MOV(uint32_t op1, uint32_t op2, CPU* cpu){
    return op2;
}

uint32_t ALU_BIC(uint32_t op1, uint32_t op2, CPU* cpu){
    return op1 & !op2;
}

uint32_t ALU_MVN(uint32_t op1, uint32_t op2, CPU* cpu){
    return !op2;
}

uint32_t (*aluOp[16])(uint32_t, uint32_t, CPU*) = {
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

uint32_t (*shiftOp[4])(uint32_t, uint8_t, CPU*) = {
    // ALU_LSL,
};

int evaluateRegOperand(uint16_t operandData, CPU *cpu, uint32_t *value){
    
    uint8_t rm = operandData & 0xF;
    uint8_t shift = (operandData >> 4) & 0xFF;
    uint32_t rValue;
    readRegister(rm, &(cpu->registers), &rValue);

    if(shift){
        uint8_t shiftType = (shift >> 1) & 0b11;
        // if register shift
        if (shift & 1){
            uint32_t rs; // shift register 
            readRegister(shift >> 4, &cpu->registers, &rs);
            rs &= 0xFF; // take lower byte
            rValue = shiftOp[shiftType](rm, rs, cpu);
        }
        else {
            rValue = shiftOp[shiftType](rValue, shift >> 3, cpu);
        }
    }
    printf("VALUE: %x",rm);
    *value = rValue;
    return 0;
}


int ALUExecute(uint32_t instruction, CPU *cpu) {
    uint8_t rn = (instruction >> 16) & 0xF;
    uint8_t rd = (instruction >> 12) & 0xF;
    uint8_t opcode = (instruction >> 21) & 0xF;
    uint32_t op2;

    // if Immediate flag set
    if ((instruction >> 25) & 0x1){
    }
    else {
        //register operand
        evaluateRegOperand((instruction & 0xFFF), cpu, &op2);

    }
    uint32_t regOut = aluOp[opcode](rn, op2, cpu);
    if ((opcode >> 2)!=0x3){
        writeRegister(rd, regOut, &cpu->registers);
    }

    return 0;
}