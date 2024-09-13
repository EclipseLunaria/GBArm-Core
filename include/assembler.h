#ifndef ASM_H
#define ASM_H
#include "core.h"
#include "utils.h"

int tokenizeInstruction(char * buffer, char tokens[16][8]);

int encodeInstruction(char * line, uint32_t *instruction);


// ALU instructions
int encodeALUInstruction(char tokens[16][8], uint32_t *encodedInstruction);
int findALUOpcode(char * token);
int isALUInstruction(char * token);
#endif