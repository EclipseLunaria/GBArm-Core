#ifndef CPU_H
#define CPU_H

#include "core.h"
#include "types.h"

#include "bus.h"
#include "registers.h"
#include <stdio.h>


int init_cpu(CPU *cpu);
int clock_cpu(CPU *cpu);

uint8_t evaluate_cond(uint8_t opcode, const uint32_t CPSR_state);

#endif