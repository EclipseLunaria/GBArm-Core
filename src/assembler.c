#include "assembler.h"
#include <stdio.h>
#include <regex.h>


int isRegister(char * r){
    return r[0] == 'R';
}
int isImmediate(char * i){
    return i[0] == '#';
}

int parseRegisterValue(char * r){
    if (!strcmp("PC", r)) return 0xE;
    if (!strcmp("LR", r)) return 0xD;

    if (r[0] != 'R'){
        // printf("\ninvalid register value\n");
        return -1;
    }
    
    for (int i = 1; i < strlen(r); ++i){
        if (!isdigit(r[i])){
            // printf("\ninvalid register value\n");
            return -1;
        }
    }
    int reg = atoi(r+1);
    if (reg < 0 || reg > 15) {
        // printf("invalid register range %d\n", reg);
        return -1;
    }
    return reg;
}
int parseImmediateValue(char * r, uint32_t *imm){
    if (r[0] != '#'){
        // printf("invalid immediate value missing #");
        return -1;
    }
    if (ishexadecimal(r+1)){
        int hv = readhexadecimal(r+1, imm);
        if (hv == 0){
            // printf("\nfailed to read hex value %s\n", r);
            return -1;
        }
        
        return 0;
    }

    // Check value is decimal
    for (int i = 1; i < strlen(r); ++i){
        if (!isdigit(r[i])){
            // printf("\ninvalid register value\n");
            return -1;
        }
    }
    
    //convert to decimal
    *imm = atoi(r+1);
    // printf("\nVAL %d\n", *imm);
    return 0;
}


uint32_t findCond(char * p){
    // printf("\nSTR: %s\n", p);
    if (strlen(p) == 0) return 0xE;
    char buf[32];
    strncpy(buf, p, 2);
    for (int i = 0; i < 15; ++i){
        if(!strcmp(COND_TYPES[i], buf)) return i;
    }
    // printf("unable to find cond match defaulting to always");
    return 0xE;
}

int isALUInstruction(char * token) {
    return findALUOpcode(token) != -1;
}

int findALUOpcode(char * token){
    char prefix[4];
    strncpy(prefix, token, 3);
    prefix[3] = '\0';
    for (int i = 0; i < 0xF; i++){
        if (!strcmp(ALU_PREFIXES[i], prefix)) return i;
    }
    return -1;
}

int getShiftCode(char * op, uint32_t *shiftCode) {
    for (int i = 0; i < 4; ++i){
        if (!strcmp(shiftOperators[i], op)) {
            *shiftCode = i;
            return 0;
        }
    }
    // printf("invalid shift value %s\n", op);
    return -1;
}

int encodeALUInstruction(char tokens[16][8], int n, uint32_t *encodedInstruction){
    *encodedInstruction = 0;

    //get opcode
    uint32_t opCode = findALUOpcode(tokens[0]);
    *encodedInstruction |= opCode << 21;

    // eval cond
    uint32_t cond = findCond(tokens[0]);
    // printf("COND: %x\n", cond);
    *encodedInstruction |= cond << 28;
    // printf("\n%x h\n", *encodedInstruction);
    
    // read dest register
    int rd = parseRegisterValue(tokens[2]);
    if (rd == -1){
        // printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rd << 12;

    // read rn
    int rn = parseRegisterValue(tokens[1]);
    // printf("RD: %d, %s", rn, tokens[1]);
    if (rn == -1){
        // printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rn << 16;

    // set S bit
    char * coffset = tokens[0] + 3;
    if (cond != 0xE) coffset += 2;
    // printf("coffset: %s\n", coffset);
    if (coffset){
        if (strlen(coffset) > 1){
            // printf("invalid argument %s\n", tokens[0]);
            return -1;
        }
        *encodedInstruction |= (coffset[0] == 'S') << 20;
    }


    // handle two register params
    if (n == 3){
        
        *encodedInstruction |= rn;
        return 0;
    }

    if (isRegister(tokens[3])){
        int rm = parseRegisterValue(tokens[3]);
        if (rm == -1) {
            return -1;
        }
        *encodedInstruction |= rm;
        // there is a shift operation performed
        if (n > 4){
            if (n == 5) {
                // printf("missing shift operand");
                return -1;
            }
            
            uint32_t shiftCode; 
            if (getShiftCode(tokens[4], &shiftCode) == -1) {
                // printf("invalid shift op");
                return -1;
            }
            // set shift code
            *encodedInstruction |= shiftCode << 5;

            if (isRegister(tokens[5])){
                *encodedInstruction |= 1 << 4;
                int rs = parseRegisterValue(tokens[5]);
                if (rs == -1) {
                    // printf("invalid register value\n");
                    return -1;
                }
                *encodedInstruction |= rs << 8;
            }
            else if (isImmediate(tokens[5])){
                uint32_t immShift;
                if(parseImmediateValue(tokens[5], &immShift) == -1){
                    return -1;
                }
                if (immShift > 31 || immShift < 0){
                    // printf("invalid immediate value %d: must be 0-31", immShift);
                    return -1;
                }
                *encodedInstruction |= immShift << 7;
            }
            else {
                // printf("invalid parameter value: %s\n", tokens[5]);
                return -1;
            }
        }
        
    }
    else if (isImmediate(tokens[3])){
        // set I bit
        *encodedInstruction |= 1 << 25;

        // TODO: handle negative offsets
        /*
            EXAMPLE: 
            MOV R0, 0x12345678
            VVVVVVVVVVVVVVVVVVV
            MOV R0, #0x12340000
            ORR R0, R0, #0x5678
        */
       uint32_t imm = 0; 
       if (parseImmediateValue(tokens[3], &imm) == -1){
        return -1;
       }

       // printf("imm: %x\n", imm);
       
       *encodedInstruction |= imm;

    } 
    else {
        // printf("invalid parameter: %s", tokens[3]);
        return 0;
    }
    return 0;
}

int executeALUInstructions(char ** instructions, int n, CPU * cpu){
    char buf[64];
    for (int i = 0; i < n; ++i){
        CPU cpuState = *cpu;
        uint32_t encoded; 
        strcpy(buf, instructions[i]);
        encodeInstruction(buf, &encoded);
        ALUExecute(encoded, cpu);
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
        // printf("\nTOKEN %d: %s\n", i, pch);
        pch = strtok(NULL, " ,;\n");
        if (i == 1 && !strncmp("MOV", tokens[0],3)) {
            strcpy(tokens[i], "R0");
            i++;
        }
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
    // printf("%s", buf);
    int n = tokenizeInstruction(buf, tokens);
    // printf("\nTokens Found: %d\n", n);
    // select
    if (isALUInstruction(tokens[0])){
        // printf("is ALU Instruction");
        int v = encodeALUInstruction(tokens, n, instruction);
        if (v == -1){
            // printf("failed to parse ALU instruction\n");
            return -1;
        } 
    }

    return 0;
}