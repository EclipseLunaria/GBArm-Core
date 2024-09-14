#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "core.h"
#include "alu.h"
#include "assembler.h"

// executes instructions in sequence if an instruction fails it returns the line which it failed
int execute_alu_instructions(char * instructions[], int n, CPU* cpu){
    
    for (int i = 0; i < n; ++i){
        char buf[64]; 
        instruction_t instruction;
        strncpy(buf, instructions[i], 32);
        printf("reading instruction %s line %d", buf, i);
        if (encode_instruction(buf, &instruction) < 0){
            printf("instruction encoding failed at %d\n", instruction);
            return i;
        }
        printf("\nexecuting instruction");
        if (alu_execute(instruction, cpu) < 0){
            printf("instruction execution failed at %d\n", instruction);
            return i;
        }
    }
    return n;
}

#endif