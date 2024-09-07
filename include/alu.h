#ifndef ALU_H
#define ALU_H
#include "core.h"
#include "cpu.h"

typedef struct ALUInstruction {
    uint8_t cond;
    uint8_t IFlag;
    uint8_t opcode;
    uint8_t setCodes;
    uint8_t rn;
    uint8_t rd;
    uint16_t op2;
} ALUInstruction;


typedef struct RegisterOpperand {
    uint16_t 
    padding:4,
    shift: 8,
    rm:4;
} RegisterOpperand;


extern uint32_t (*aluOp[16])(uint32_t, uint32_t, CPU*);
uint32_t ALU_AND(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_EOR(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_SUB(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_RSB(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_ADD(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_ADC(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_SBC(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_RSC(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_TST(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_TEQ(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_CMP(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_CMN(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_ORR(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_MOV(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_BIC(uint32_t op1, uint32_t op2, CPU* cpu);
uint32_t ALU_MVN(uint32_t op1, uint32_t op2, CPU* cpu);



// ALU OPERATIONS

int ALUExecute(uint32_t instruction, CPU *cpu);

#endif