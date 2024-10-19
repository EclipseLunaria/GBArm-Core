#ifndef CORE_H
#define CORE_H

#include <assert.h>
#include <stdint.h>
#include <memory.h>

#include "types.h"
#include "memory_bus.h"


// CPU Funtionality

typedef struct CPU {
    MemoryBus memory;
    CpuRegister registers;
    CPSR *CPSR;
} CPU;

int init_cpu(CPU *cpu);

#endif
