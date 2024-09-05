#include "cond.h"
#include <stdio.h>

uint8_t evaluate_cond(uint8_t opcode, const uint32_t CPSR_state){
    CPSR * cpsr = (CPSR *)&CPSR_state;
    uint8_t evalStates = 
         (cpsr->Z << 0) 
        |(cpsr->C << 1)
        |(cpsr->N << 2)
        |(cpsr->V << 3)
        |((cpsr->C && !cpsr->Z) << 4)
        |((cpsr->N == cpsr->V) << 5)
        |((!cpsr->Z && (cpsr->N==cpsr->V))<< 6)
        |(cpsr->V << 7);
    uint8_t v = (1 << (opcode/2)) &evalStates;

    return opcode % 2 == 0 ? v : !v;
}