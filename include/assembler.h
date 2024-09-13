#ifndef ASM_H
#define ASM_H
#include "core.h"
#include "utils.h"

#define STREAM_SIZE 2048

typedef struct InstructionStream {
    uint32_t instructions[STREAM_SIZE];
    uint32_t length;
} InstructionStream;

int initIStream(InstructionStream * iStream);
int writeIStream(InstructionStream * iStream, uint32_t instruction);

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
int encodeALUInstruction(char tokens[16][8], int n, uint32_t *encodedInstruction);
int findALUOpcode(char * token);
int isALUInstruction(char * token);
#endif