#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "core.h"
#include "registers.h"


typedef struct BranchInstruction
{
    unsigned
    cond:4,
    opcode:3,
    isLinked: 1,
    signedImmediate: 24;
} BranchInstruction; 

int B(CPU * cpu);
int BL(CPU * cpu);



#endif