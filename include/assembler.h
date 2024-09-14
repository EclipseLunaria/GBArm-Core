#ifndef ASM_H
#define ASM_H
#include "core.h"
#include "alu.h"
#include "utils.h"

int tokenize_instruction(char * buffer, char tokens[16][8]);
int encode_instruction(char * line, uint32_t *instruction);

// Value Parsing
// register
int is_register(char * r);
int parse_register_value(char * r);
// immediate
int is_immediate(char * i);
int parse_immediate_value(char * r, uint32_t *imm);

// ALU instructions
int encode_alu_instruction(char tokens[16][8], int n, uint32_t *encodedInstruction);
int find_alu_opcode(char * token);
int is_alu_instruction(char * token);
#endif