#include "impl_core.h"
#include "registers.h"
#include "memory_bus.h"

int init_cpu(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
    init_registers(&cpu->registers);
    cpu->CPSR = (CPSR *)&cpu->registers.cpsr;
    init_memory_bus(GBA_SECTORS, 7, &cpu->memory);
    return 0;
}



uint8_t evaluate_cond(uint8_t opcode, uint32_t CPSR_state) {
    if (opcode == 0xE) return 1;
    CPSR *cpsr = (CPSR *)&CPSR_state;
    uint8_t evalStates = (cpsr->Z << 0) | (cpsr->C << 1) | (cpsr->N << 2) | (cpsr->V << 3) |
                         ((cpsr->C && !cpsr->Z) << 4) | ((cpsr->N == cpsr->V) << 5) |
                         ((!cpsr->Z && (cpsr->N == cpsr->V)) << 6) | (cpsr->V << 7);
    uint8_t v = evalStates >> (opcode / 2) & 1;
    return opcode % 2 == 0 ? v : !v;
}
