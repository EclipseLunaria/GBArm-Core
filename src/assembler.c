#include "assembler.h"
#include <stdio.h>

char * COND_TYPES[] = {
    "EQ",
    "NE",
    "CS",
    "CC",
    "MI",
    "PL",
    "VS",
    "VC",
    "HI",
    "LS",
    "GE",
    "LT",
    "GT",
    "LE",
    "AL",
};

uint32_t findCond(char * p){
    printf("STR: %s", p);
    if (strlen(p) == 0) return 0xE;
    char buf[32];
    strcpy(buf, p);
    for (int i = 0; i < 15; ++i){
        if(!strcmp(COND_TYPES[i], buf)) return i;
    }
    printf("unable to find cond match defaulting to always");
    return 0xE;
}

char * ALU_PREFIXES[] = {
    "AND",   // Bitwise AND
    "EOR",   // Bitwise Exclusive OR
    "SUB",   // Subtract
    "RSB",   // Reverse Subtract
    "ADD",   // Addition
    "ADC",   // Add with Carry
    "SBC",   // Subtract with Carry
    "RSC",   // Reverse Subtract with Carry
    "TST",   // Test (AND)
    "TEQ",   // Test Equivalence (EOR)
    "CMP",   // Compare
    "CMN",   // Compare Negated
    "ORR",   // Bitwise OR
    "MOV",   // Move
    "BIC",   // Bitwise Clear (AND NOT)
    "MVN"    // Move Not
};

int findALUOpcode(char * token){
    char prefix[4];
    strncpy(prefix, token, 3);
    prefix[3] = '\0';
    for (int i = 0; i < 0xF; i++){
        if (!strcmp(ALU_PREFIXES[i], prefix)) return i;
    }
    return -1;
}

int isALUInstruction(char * token) {
    return findALUOpcode(token) != -1;
}

int encodeALUInstruction(char  tokens[16][8], uint32_t *encodedInstruction){
    *encodedInstruction = 0;

    //get opcode
    uint32_t opCode = findALUOpcode(tokens[0]);
    *encodedInstruction |= opCode << 21;

    // eval cond
    uint32_t cond = findCond(tokens[0]);
    printf("COND: %x", cond);
    *encodedInstruction |= cond << 28;
    printf("\n%x h\n", *encodedInstruction);
    return 0;
}

int tokenizeInstruction(char * buffer, char tokens[16][8]) {
    int i = 0;
    char * pch;
    pch = strtok(buffer, " ,");
    while (pch != NULL && i < 16) {
        printf("TOKEN %d: %s\n", i, pch);
        strcpy(tokens[i], pch);  // Copy the token into the array
        i++;
        pch = strtok(NULL, " ,");
    }

    // Null terminate remaining tokens to prevent garbage data
    for (int j = i; j < 16; j++) {
        tokens[j][0] = '\0';
    }

    return 0;
}

int encodeInstruction(char * line, uint32_t *instruction){
    char buf[512];
    char tokens[16][8];
    strcpy(buf, line);
    int n = tokenizeInstruction(buf, tokens);

    // select
    if (isALUInstruction(tokens[0])){
        printf("is ALU Instruction");
    }
    printf("LINE: %s, %d", buf, n);

    // identify
    return 0;
}