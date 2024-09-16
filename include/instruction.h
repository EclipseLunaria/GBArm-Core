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
int MSR_IMM(instruction_t instruction, CPU *cpu);
//Single Data Transfer: LDR, STR, PLD
int SDT(instruction_t instruction, CPU *cpu);

// store methods
int store_half_word(address_t address, uint64_t lword, CPU* cpu);
int load_double_word(address_t address, uint64_t lword, CPU *cpu);


int STDT(instruction_t instruction, CPU *cpu);
#endif