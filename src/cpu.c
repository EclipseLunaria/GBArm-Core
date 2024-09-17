#include "cpu.h"
#include "core.h"

int init_cpu(CPU *cpu){
    memset(cpu, 0, sizeof(CPU));
    init_registers(&cpu->registers);
    cpu->CPSR = (CPSR *)&cpu->registers.cpsr;
    return 0;
}

int fetchInstruction(CPU * cpu) {
    read_word(*cpu->registers.PC,&cpu->loaded_instruction);
    *cpu->registers.PC += 4;
    return 0;
}

int clock_cpu(CPU *cpu){
    cpu->clock_cycles += 1;

    // if no sleep cycles -> wait
    if (cpu->sleep_cycles){
        --cpu->sleep_cycles;
        return 0;
    }

    // load instruction to cpu
    fetchInstruction(cpu);

    return 0;
}

/*
-------------------------

CSPR LOGIC REGION START

-------------------------

*/



uint8_t evaluate_cond(uint8_t opcode, const uint32_t CPSR_state){
    printf("OPCODE: %x", opcode);
    if (opcode == 0xE) return 1;
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


