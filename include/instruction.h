#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "core.h"
#include "registers.h"
#include "barrel_shifter.h"


int B(CPU * cpu);

//MRS – Move PSR into General-Purpose Register
int is_mrs(uint32_t instruction);
int MRS(instruction_t instruction_t, CPU* cpu);

int is_msr_reg(instruction_t instruction);
int MSR_REG(instruction_t instruction, CPU * cpu);

int is_msr_imm(instruction_t instruction);
int MSR_IMM(instruction_t instruction);

#endif