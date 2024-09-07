#include "cpu.h"


int initCpu(CPU *cpu){
    initCpuRegisters(&cpu->registers);

    return 0;
}

int clock(CPU *cpu){
    cpu->clockCycle += 1;

    // if no sleep cycles -> wait
    if (cpu->sleepCycles){
        --cpu->sleepCycles;
        return 0;
    }

    // load instruction to cpu
    
    return 0;
}

/*
-------------------------

CSPR LOGIC REGION START

-------------------------

*/


uint8_t CSPR_get_flag(const CPSRFLAGS f, uint32_t * pCspr){
    if (*pCspr&f) return 1;
    return 0;
}
void CSPR_set_flag(const CPSRFLAGS f, const uint8_t value, uint32_t * pCspr){
    if (value) {
        *pCspr = *pCspr | f;
    }
    else {
        *pCspr = *pCspr & !f;
    }
    
}

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


/*
-------------------------

CSPR LOGIC REGION END

-------------------------

*/

