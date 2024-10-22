#include "interrupt.h"
#include "registers.h"

// Software Interrupt
int SWI(instruction_t instruction, CPU *cpu) {
    set_mode(1, &cpu->registers);
    write_register(14, *cpu->registers.PC, &cpu->registers);
    write_register(15, 0x08, &cpu->registers);
    return 0;
}
