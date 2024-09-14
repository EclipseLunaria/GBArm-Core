#ifndef INSTRUCTION_STREAM_H
#define INSTRUCTION_STREAM_H
#include "core.h"

#define STREAM_SIZE 2048
#define INSTRUCTION_BUFFER 32

typedef struct InstructionNode {
    uint32_t encoded;
    
} InstructionNode;

typedef struct InstructionStream {
    char sInstruction[STREAM_SIZE][INSTRUCTION_BUFFER]; // Instruction Strings
    uint32_t encodings[STREAM_SIZE];                    // Encoded Instruction Value
    uint32_t encodingMap[STREAM_SIZE];                  // Maps Encodings to assembly instruction
    uint32_t length;
} InstructionStream;

int initIStream(InstructionStream * iStream);
int writeIStream(InstructionStream * iStream, uint32_t instruction );


#endif