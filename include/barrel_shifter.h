#ifndef BARREL_SHIFTER_H
#define BARREL_SHIFTER_H
#include "core.h"


extern int (*shiftOp[4])(uint32_t, uint8_t, BS_FLAGS*, uint32_t*);
int BS_LSL(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_LSR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_ASR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);
int BS_ROR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result);


#endif