#ifndef ASM_H
#define ASM_H
#include "core.h"
#include "alu.h"
#include "utils.h"

int tokenizeInstruction(char * buffer, char tokens[16][8]);
int encodeInstruction(char * line, uint32_t *instruction);

// Value Parsing
// register
int isRegister(char * r);
int parseRegisterValue(char * r);
// immediate
int isImmediate(char * i);
int parseImmediateValue(char * r, uint32_t *imm);

// ALU instructions
int executeALUInstructions(char ** instructions, int n, CPU * cpu);
int encodeALUInstruction(char tokens[16][8], int n, uint32_t *encodedInstruction);
int findALUOpcode(char * token);
int isALUInstruction(char * token);
#endif