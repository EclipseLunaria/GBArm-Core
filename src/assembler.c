#include "assembler.h"
#include <stdio.h>
#include <regex.h>


int is_register(char * r){
    return r[0] == 'R';
}
int is_immediate(char * i){
    return i[0] == '#';
}

int parse_register_value(char * r){
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
int parse_immediate_value(char * r, uint32_t *imm){
    if (r[0] != '#'){
        // printf("invalid immediate value missing #");
        return -1;
    }
    if (is_hex(r+1)){
        int hv = read_hex(r+1, imm);
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


uint32_t find_cond(char * p){
    // printf("\nSTR: %s\n", p);
    if (strlen(p) == 0) return 0xE;
    char buf[32];
    strncpy(buf, p, 2);
    for (int i = 0; i < 15; ++i){
        if(!strcmp(COND_TYPE_STRS[i], buf)) return i;
    }
    // printf("unable to find cond match defaulting to always");
    return 0xE;
}

int is_alu_instruction(char * token) {
    return find_alu_opcode(token) != -1;
}

int find_alu_opcode(char * token){
    char prefix[4];
    strncpy(prefix, token, 3);
    prefix[3] = '\0';
    for (int i = 0; i < 0xF; i++){
        if (!strcmp(ALU_OPCODE_STRS[i], prefix)) return i;
    }
    THROW_ERROR("Invald ALU OP Token: %s", token);
}

int get_shift_code(char * op, uint32_t *shift_code) {
    for (int i = 0; i < 4; ++i){
        if (!strcmp(SHIFT_OP_STRS[i], op)) {
            *shift_code = i;
            return 0;
        }
    }
    // printf("invalid shift value %s\n", op);
    return -1;
}

int encode_alu_instruction(char tokens[16][8], int n, uint32_t *encodedInstruction){
    *encodedInstruction = 0;
    printf("TOKEN VAL: %s", tokens[0]);
    //get opcode
    uint32_t opCode = find_alu_opcode(tokens[0]);
    *encodedInstruction |= opCode << 21;
    printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
    // eval cond
    uint32_t cond = find_cond(tokens[0]);
    // printf("COND: %x\n", cond);
    *encodedInstruction |= cond << 28;
    // printf("\n%x h\n", *encodedInstruction);
    printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
    
    // read dest register
    int rd = parse_register_value(tokens[1]);
    if (rd == -1){
        // printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rd << 12;

    // read rn
    int rn = parse_register_value(tokens[2]);
    printf("\nRD: %d, %s\n", rn, tokens[2]);
    if (rn == -1){
        printf("Invalid register value");
        return -1;
    }
    *encodedInstruction |= rn << 16;
    printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);

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

    printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);

    // handle two register params
    if (n == 3){
        
        *encodedInstruction |= rd;
        return 0;
    }

    

    if (is_register(tokens[3])){
    printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
        int rm = parse_register_value(tokens[3]);
        if (rm == -1) {
            return -1;
        }
        *encodedInstruction |= rm;
        printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
        // there is a shift operation performed
        if (n > 4){
            if (n == 5) {
                printf("missing shift operand");
                return -1;
            }
            
            uint32_t shift_code; 
            if (get_shift_code(tokens[4], &shift_code) == -1) {
                // printf("invalid shift op");
                return -1;
            }
            // set shift code
            *encodedInstruction |= shift_code << 5;

            if (is_register(tokens[5])){
                *encodedInstruction |= 1 << 4;
                int rs = parse_register_value(tokens[5]);
                if (rs == -1) {
                    // printf("invalid register value\n");
                    return -1;
                }
                *encodedInstruction |= rs << 8;
            }
            else if (is_immediate(tokens[5])){
                uint32_t immShift;
                if(parse_immediate_value(tokens[5], &immShift) == -1){
                    return -1;
                }
                if (immShift > 31 || immShift < 0){
                    printf("invalid immediate value %d: must be 0-31", immShift);
                    return -1;
                }
                *encodedInstruction |= immShift << 7;
            }
            else {
                // printf("invalid parameter value: %s\n", tokens[5]);
                return -1;
            }
        }
        
        printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
        
    }
    else if (is_immediate(tokens[3])){
        printf("\nENCODED INSTRUCTION %x LINE %d\n", *encodedInstruction, __LINE__);
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
       if (parse_immediate_value(tokens[3], &imm) == -1){
        return -1;
       }

       // printf("imm: %x\n", imm);
       
       *encodedInstruction |= imm;

    } 
    else {
        printf("invalid parameter: %s", tokens[3]);
        return 0;
    }
    return 0;
}



int tokenize_instruction(char * buffer, char tokens[16][8]) {
    int i = 0;
    char * pch;
    pch = strtok(buffer, " ,;\n");

    while (pch != NULL && i < 16) {
        strcpy(tokens[i], pch);  // Copy the token into the array
        i++;
        printf("\nTOKEN %d: %s\n", i, pch);
        pch = strtok(NULL, " ,;\n");
        if (i == 1 && (!strncmp("MOV", tokens[0],3))) {
            strcpy(tokens[i], pch);
            i++;
        }
    }

    // Null terminate remaining tokens to prevent garbage data
    for (int j = i; j < 16; j++) {
        tokens[j][0] = '\0';
    }

    return i;
}

int encode_instruction(char * line, uint32_t *instruction){
    char buf[512];
    char tokens[16][8];
    strcpy(buf, line);
    toUpper(buf);
    printf("%s", buf);
    int n = tokenize_instruction(buf, tokens);
    printf("\nTokens Found: %d\n", n);
    // select
    if (is_alu_instruction(tokens[0])){
        printf("is ALU Instruction");
        CHECK_ERROR(encode_alu_instruction(tokens, n, instruction), "failed to parse ALU instruction\n")
        // int v = encode_alu_instruction(tokens, n, instruction);
        // if (v == -1){
        //     // printf("failed to parse ALU instruction\n");
        //     return -1;
        // } 
    }

    return 0;
}