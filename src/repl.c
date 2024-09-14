#include "repl.h"


void run_repl_terminal(){
    printf("Initializing CPU\n");

    CPU cpu;
    init_cpu(&cpu);

    while (1) {
        dump_registers(&cpu);
        uint32_t encoded_value;
        char buf[128];
        printf("\nEnter ASM Command: ");
        fgets(buf, sizeof(buf), stdin);
        printf("%s", buf);
        encode_instruction(buf, &encoded_value);
        printf("Instruction: %x\n", encoded_value);
        alu_execute(encoded_value, &cpu);
        
    }
    dump_registers(&cpu);

}
