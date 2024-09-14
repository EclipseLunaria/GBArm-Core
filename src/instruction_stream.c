#include "instruction_stream.h"
int init_istream(InstructionStream * iStream){
    memset(iStream,0, sizeof(InstructionStream));

    return 0;
}

int write_istream(InstructionStream * iStream, uint32_t instruction){
    if (iStream->length == STREAM_SIZE) {
        printf("Stream is full");
        return -1;
    }
    iStream->encodings[iStream->length] = instruction;
    iStream->length++;
    return 0;
}

