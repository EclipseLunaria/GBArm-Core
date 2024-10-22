#include "barrel_shifter.h"

int (*shiftOp[4])(uint32_t, uint8_t, BS_FLAGS*, uint32_t*) = {
    BS_LSL,
    BS_LSR,
    BS_ASR,
    BS_ROR
};

int BS_LSL(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result){
    if (shift_amount == 0){
        *result = value;
        return 0;
    }
    *result = shift_amount < 32 ? value << shift_amount : 0;
    flags->C = shift_amount < 32 ? (value >> (32-shift_amount)) & 1 : 0;
    return 0;
}

int BS_LSR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result){
    if (shift_amount == 0){
        *result = value;
        return 0;
    }
    *result = shift_amount < 32 ? value >> shift_amount : 0;
    flags->C = shift_amount < 32 ? (value >> (shift_amount-1)) & 1 : 0;
    return 0;
}


int BS_ASR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result){
    uint32_t msb = value & 0x80000000;
    if (shift_amount >= 32) {
        *result = msb ? 0xFFFFFFFF : 0;
        flags->C = msb ? 1 : 0;
        return 0;
    }
    *result = value >> shift_amount;

    if (msb) {
        uint32_t mask = (1 << (32-shift_amount)) - 1;
        *result |= ~mask;
    }

    flags->C = shift_amount > 0 ? (value >> (shift_amount - 1)) & 1 : 0;

    return 0;
    
}

int BS_ROR(uint32_t value, uint8_t shift_amount, BS_FLAGS* flags, uint32_t *result){
    shift_amount %= 32;
    *result = (value >> shift_amount) | (value << (32 - shift_amount));
    flags->C = value >> 31;
    return 0;
}
