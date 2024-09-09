#ifndef BARREL_SHIFTER_H
#define BARREL_SHIFTER_H
#include "core.h"

typedef struct BS_FLAGS {
    uint8_t
    unused:3,
    IsArithmetic:1,
    Z:1,
    N:1,
    C:1,
    V:1;

} BS_FLAGS;


int BS_LSL(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_LSR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_ASR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_ROR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);

#endif