#include "repl.h"


void run_repl_terminal(){
    printf("Initializing CPU\n");

    CPU cpu;
    initCpu(&cpu);

    while (1) {
        dumpRegisters(&cpu);
        uint32_t encodedValue;
        char buf[128];
        printf("\nEnter ASM Command: ");
        fgets(buf, sizeof(buf), stdin);
        printf("%s", buf);
        encodeInstruction(buf, &encodedValue);
        printf("Instruction: %x\n", encodedValue);
        ALUExecute(encodedValue, &cpu);
        
    }
    dumpRegisters(&cpu);

}
