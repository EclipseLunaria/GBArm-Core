#ifndef CPU_H
#define CPU_H

#include <stdio.h>

#include "core.h"
#include "registers.h"
#include "types.h"

int init_cpu(CPU *cpu);
int clock_cpu(CPU *cpu);

uint8_t evaluate_cond(uint8_t opcode, uint32_t CPSR_state);

int dump_cpu_state(CPU *cpu);

#endif