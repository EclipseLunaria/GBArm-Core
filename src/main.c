#include "cpu.h"

int execInstruction(CPU * cpu){
    printf("\nHello World\n");
    return 0;
}

typedef struct Instruction {
    char mnemonic[6];
    int (*execute)(CPU *);

} Instruction;

int main(){
    CPU cpu;
    initCpu(&cpu);

    Instruction i;
    i.execute = &execInstruction;

    i.execute(&cpu);



    // Invoking fun() using fun_ptr

    return 0;

    return 0;

}