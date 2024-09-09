#include "barrel_shifter.h"


int BS_LSL(uint32_t value, uint8_t shiftAmt, BS_FLAGS* flags, uint32_t *result){
    if (shiftAmt == 0){
        *result = value;
        return 0;
    }
    *result = shiftAmt < 32 ? value << shiftAmt : 0;
    //set flags.
    flags->C = shiftAmt < 32 ? (value >> (32-shiftAmt)) & 1 : 0;
    

    return 0;

}