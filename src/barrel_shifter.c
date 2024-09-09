#include "barrel_shifter.h"


int BS_LSL(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result){
    if (shiftAmt == 0){
        *result = value;
        return 0;
    }
    *result = shiftAmt < 32 ? value << shiftAmt : 0;
    flags->C = shiftAmt < 32 ? (value >> (32-shiftAmt)) & 1 : 0;
    return 0;
}

int BS_LSR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result){
    if (shiftAmt == 0){
        *result = value;
        return 0;
    }
    *result = shiftAmt < 32 ? value >> shiftAmt : 0;
    flags->C = shiftAmt < 32 ? (value >> (shiftAmt-1)) & 1 : 0;
    return 0;
}


int BS_ASR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result){
    uint32_t msb = value & 0x80000000;
    if (shiftAmt >= 32) {
        *result = msb ? 0xFFFFFFFF : 0;
        flags->C = msb ? 1 : 0;
        return 0;
    }
    *result = value >> shiftAmt;

    if (msb) {
        uint32_t mask = (1 << (32-shiftAmt)) - 1;
        *result |= ~mask;
    }

    flags->C = shiftAmt > 0 ? (value >> (shiftAmt - 1)) & 1 : 0;

    return 0;
    
}

int BS_ROR(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result){
    shiftAmt %= 32;
    *result = (value >> shiftAmt) | (value << (32 - shiftAmt));
    flags->C = value >> 31;
    return 0;
}