#include "core.h"
#include "cpu.h"
#include "repl.h"
int main(){
    CPU cpu;
    initCpu(&cpu);
    run_repl_terminal();
    // while (1) {
    //     // uint32_t encodedValue;
    //     // char buf[128];
    //     // printf("Enter ASM Command: ");
    //     // fgets(buf, sizeof(buf), stdin);
    //     // printf("%s", buf);
    //     // encodeInstruction(buf, &encodedValue);
    //     // printf("ASM COMMAND: %s, Instruction: %x\n", buf, encodedValue);
    //     // char * line = "ADDS R1 r2 #100";
        
    // }


    return 0;

}