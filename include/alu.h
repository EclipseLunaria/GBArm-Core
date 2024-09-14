#ifndef ALU_H
#define ALU_H
#include "core.h"
#include "cpu.h"
#include "barrel_shifter.h"

extern int (*aluOp[16])(uint32_t, uint32_t, BS_FLAGS*, uint32_t*);
int ALU_AND(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_EOR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_SUB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);

// NEEDS TESTING
int ALU_RSB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_ADD(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_ADC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_SBC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_RSC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_TST(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_TEQ(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_CMP(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_CMN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_ORR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_MOV(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_BIC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);
int ALU_MVN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result);

int eval_register_operand(uint32_t operandBits, BS_FLAGS *flags, CPU *cpu, uint32_t *result);

int alu_execute(uint32_t instruction, CPU *cpu);

#endif