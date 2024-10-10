#include "constants.h"
// execution modes
#define USER_MODE 0
#define SUPERVISOR_MODE 1

char* COND_TYPE_STRS[] = {
    "EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE", "AL",
};

char* ALU_OPCODE_STRS[] = {
    "AND",  // Bitwise AND
    "EOR",  // Bitwise Exclusive OR
    "SUB",  // Subtract
    "RSB",  // Reverse Subtract
    "ADD",  // Addition
    "ADC",  // Add with Carry
    "SBC",  // Subtract with Carry
    "RSC",  // Reverse Subtract with Carry
    "TST",  // Test (AND)
    "TEQ",  // Test Equivalence (EOR)
    "CMP",  // Compare
    "CMN",  // Compare Negated
    "ORR",  // Bitwise OR
    "MOV",  // Move
    "BIC",  // Bitwise Clear (AND NOT)
    "MVN"   // Move Not
};

char* SHIFT_OP_STRS[4] = {"LSL", "LSR", "ASR", "ROR"};