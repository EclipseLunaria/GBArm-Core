#ifndef ALU_H
#define ALU_H
#include "core.h"
#include "cpu.h"


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

// Shift Operations
extern uint32_t (*shiftOp[4])(uint32_t, uint8_t, CPU*);
uint32_t ALU_LSL(uint32_t value, uint8_t shitAmt, CPU* cpu);
uint32_t ALU_LSR(uint32_t value, uint8_t shitAmt, CPU* cpu);
uint32_t ALU_ASR(uint32_t value, uint8_t shitAmt, CPU* cpu);
uint32_t ALU_ROR(uint32_t value, uint8_t shitAmt, CPU* cpu);


// ALU OPERATIONS

int ALUExecute(uint32_t instruction, CPU *cpu);

#endif