#ifndef BRANCH_H
#define BRANCH_H

#include "core.h"
#include "types.h"

int B(instruction_t instruction, CPU *cpu);
int BX(instruction_t instruction, CPU *cpu);

#endif
