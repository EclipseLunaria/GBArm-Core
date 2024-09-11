#include "core.h"
#include "registers.h"

//Multiply and Multiply-Accumulate (MUL, MLA)
int handleMultiply(uint32_t instruction, CPU* cpu);

// Multiply Long and Multiply-Accumulate Long (MULL,MLAL)
int handleLongMultiply(uint32_t instruction, CPU* cpu);
