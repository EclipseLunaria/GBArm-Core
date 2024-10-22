#ifndef IMPL_CORE
#define IMPL_CORE
#include <stdint.h>

uint8_t evaluate_cond(uint8_t opcode, uint32_t CPSR_state);

typedef struct BS_FLAGS {
    uint8_t unused : 3, Is_arithmetic : 1, Z : 1, N : 1, C : 1, V : 1;
} BS_FLAGS;


#endif
