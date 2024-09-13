#include "assembler.h"
#include <stdio.h>
#include <regex.h>

int isRegister(char * r){
    return r[0] == 'R';
}
int isImmediate(char * i){
    return i[0] == '#';
}

int readRegisterValue(char * r){
    if (!strcmp("PC", r)) return 0xE;
    if (!strcmp("LR", r)) return 0xD;

    if (r[0] != 'R'){
        printf("\ninvalid register value\n");
        return -1;
    }
    
    for (int i = 1; i < strlen(r); ++i){
        if (!isdigit(r[i])){
            printf("\ninvalid register value\n");
            return -1;
        }
    }
    printf("STRR: %s", r+1);
    int reg = atoi(r+1);
    if (reg < 0 || reg > 15) {
        printf("invalid register range %d\n", reg);
        return -1;
    }
    printf("\nreg value: %d\n", reg);
    return reg;
}
int readImmediateValue(char * r){
    if (r[0] != '#'){
        printf("invalid immediate value missing #");
        return -1;
    }
    for (int i = 1; i < strlen(r); ++i){
        if (!isdigit(r[i])){
            printf("\ninvalid register value\n");
            return -1;
        }
    }
    int val = atoi(r+1);
    return val;
}

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
    printf("\nSTR: %s\n", p);
    if (strlen(p) == 0) return 0xE;
    char buf[32];
    strncpy(buf, p, 2);
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

int encodeALUInstruction(char tokens[16][8], int n, uint32_t *encodedInstruction){
    *encodedInstruction = 0;

    //get opcode
    uint32_t opCode = findALUOpcode(tokens[0]);
    *encodedInstruction |= opCode << 21;

    // eval cond
    uint32_t cond = findCond(tokens[0]);
    printf("COND: %x\n", cond);
    *encodedInstruction |= cond << 28;
    printf("\n%x h\n", *encodedInstruction);

    // read dest register
    int rd = readRegisterValue(tokens[1]);
    printf("RD: %d, %s", rd, tokens[1]);
    if (rd == -1){
        printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rd << 16;

    // set S bit
    char * coffset = tokens[0] + 3;
    if (cond != 0xE) coffset += 2;
    printf("coffset: %s\n", coffset);
    if (coffset){
        if (strlen(coffset) > 1){
            printf("invalid argument %s\n", tokens[0]);
            return -1;
        }
        *encodedInstruction |= (coffset[0] == 'S') << 20;
    }

    // read rn
    printf("REG VAL: %s", tokens[2]);
    int rn = readRegisterValue(tokens[2]);
    if (rn == -1){
        printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rn << 12;

    // handle two register params
    if (n == 3){
        *encodedInstruction |= rn;
        return 0;
    }

    if (isRegister(tokens[3])){
        int rm = readRegisterValue(tokens[3]);
        if (rm == -1) {
            return -1;
        }
        *encodedInstruction |= rm;
    }
    else if (isImmediate(tokens[3])){
        
    } 
    else {
        printf("invalid parameter: %s", tokens[3]);
    }
    return 0;
}

int tokenizeInstruction(char * buffer, char tokens[16][8]) {
    int i = 0;
    char * pch;
    pch = strtok(buffer, " ,;\n");
    while (pch != NULL && i < 16) {
        strcpy(tokens[i], pch);  // Copy the token into the array
        i++;
        printf("\nTOKEN %d: %s\n", i, pch);
        pch = strtok(NULL, " ,;\n");
    }

    // Null terminate remaining tokens to prevent garbage data
    for (int j = i; j < 16; j++) {
        tokens[j][0] = '\0';
    }

    return i;
}

int encodeInstruction(char * line, uint32_t *instruction){
    char buf[512];
    char tokens[16][8];
    strcpy(buf, line);
    toUpper(buf);
    printf("%s", buf);
    int n = tokenizeInstruction(buf, tokens);
    printf("\nTokens Found: %d\n", n);
    // select
    if (isALUInstruction(tokens[0])){
        printf("is ALU Instruction");
        int v = encodeALUInstruction(tokens, n, instruction);
        if (v == -1){
            printf("failed to parse ALU instruction\n");
            return -1;
        } 
    }

    // identify
    return 0;
}