#ifndef PSR_H
#define PSR_H

#include "core.h"
#include "constants.h"
// MRS – Move PSR into General-Purpose Register
int is_mrs(uint32_t instruction);
int MRS(instruction_t instruction_t, CPU *cpu);

int is_msr_reg(instruction_t instruction);
int MSR_REG(instruction_t instruction, CPU *cpu);

int is_msr_imm(instruction_t instruction);
int MSR_IMM(instruction_t instruction, CPU *cpu);

#endif
