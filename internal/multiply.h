#include "core.h"
#include "registers.h"

//Multiply and Multiply-Accumulate (MUL, MLA)
int handle_multiply(uint32_t instruction, CPU* cpu);

// Multiply Long and Multiply-Accumulate Long (MULL,MLAL)
int handle_long_multiply(uint32_t instruction, CPU* cpu);
