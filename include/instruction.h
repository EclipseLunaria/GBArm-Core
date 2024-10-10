#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "alu.h"
#include "barrel_shifter.h"
#include "core.h"
#include "multiply.h"
#include "registers.h"

int execute_instruction(instruction_t instruction, CPU *cpu);

int B(instruction_t instruction, CPU *cpu);

// MRS – Move PSR into General-Purpose Register
int is_mrs(uint32_t instruction);
int MRS(instruction_t instruction_t, CPU *cpu);

int is_msr_reg(instruction_t instruction);
int MSR_REG(instruction_t instruction, CPU *cpu);

int is_msr_imm(instruction_t instruction);
int MSR_IMM(instruction_t instruction, CPU *cpu);
// Single Data Transfer: LDR, STR, PLD
int SDT(instruction_t instruction, CPU *cpu);

int STDT(instruction_t instruction, CPU *cpu);
// Block Data Transfer
int BDT(instruction_t instruction, CPU *cpu);

// Single data swap
int SWP(instruction_t instruction, CPU *cpu);

// Software Interrupt
int SWI(instruction_t instruction, CPU *cpu);
#endif