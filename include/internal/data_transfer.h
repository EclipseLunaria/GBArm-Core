#include "core.h"

// Single Data Transfer: LDR, STR, PLD
int SDT(instruction_t instruction, CPU *cpu);

int STDT(instruction_t instruction, CPU *cpu);
// Block Data Transfer
int BDT(instruction_t instruction, CPU *cpu);

// Single data swap
int SWP(instruction_t instruction, CPU *cpu);

