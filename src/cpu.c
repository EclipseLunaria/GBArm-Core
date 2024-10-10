#include "cpu.h"

#include "core.h"

int init_cpu(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
    init_registers(&cpu->registers);
    cpu->CPSR = (CPSR *)&cpu->registers.cpsr;
    init_memory_bus(GBA_SECTORS, 7, &cpu->memory);
    return 0;
}

int clock_cpu(CPU *cpu) {
    cpu->clock_cycles += 1;

    // if no sleep cycles -> wait
    if (cpu->sleep_cycles) {
        --cpu->sleep_cycles;
        return 0;
    }

    // load instruction to cpu

    return 0;
}

int dump_cpu_state(CPU *cpu) {
    printf("Active Registers:\n");
    int col_printed = 0;
    for (int i = 0; i < 16; ++i) {
        printf("%sR%-2d: %x      %s",
               (cpu->registers.current_registers->p_registers[i] != (&cpu->registers.register_data.registers[i])) ? "*"
                                                                                                                  : "",
               i, *cpu->registers.current_registers->p_registers[i], i % 4 == 0 ? "" : "");
        col_printed++;

        if (col_printed == 4) {
            col_printed = 0;
            printf("\n");
        }
        // if (i % 4 == 0) printf("\n");
    }

    printf("Program State:\n");
    printf("PC:    0x%08x,     LR: 0x%08x\nCPSR:  0x%08x,     Execution Mode: %d\n", *cpu->registers.PC,
           *cpu->registers.LR, cpu->registers.cpsr, cpu->registers.current_mode);

    return 0;
}

uint8_t evaluate_cond(uint8_t opcode, uint32_t CPSR_state) {
    if (opcode == 0xE) return 1;
    CPSR *cpsr = (CPSR *)&CPSR_state;
    uint8_t evalStates = (cpsr->Z << 0) | (cpsr->C << 1) | (cpsr->N << 2) | (cpsr->V << 3) |
                         ((cpsr->C && !cpsr->Z) << 4) | ((cpsr->N == cpsr->V) << 5) |
                         ((!cpsr->Z && (cpsr->N == cpsr->V)) << 6) | (cpsr->V << 7);
    uint8_t v = evalStates >> (opcode / 2) & 1;
    printf("\neval: %x\n", evalStates);
    return opcode % 2 == 0 ? v : !v;
}
