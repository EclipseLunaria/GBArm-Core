#ifndef BARREL_SHIFTER_H
#define BARREL_SHIFTER_H
#include "impl_core.h"

extern int (*shiftOperation[4])(uint32_t, uint8_t, BS_FLAGS*, uint32_t*);
int BS_LSL(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result);
int BS_LSR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result);
int BS_ASR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result);
int BS_ROR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result);


#endif
