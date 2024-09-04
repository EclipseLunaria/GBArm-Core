#include "cpu.h"



/*
-------------------------

CSPR LOGIC REGION START

-------------------------

*/

uint32_t CSPR_state = 0;

uint8_t CSPR_get_flag(const CPSRFLAGS f){
    if (CSPR_state&f) return 1;
    return 0;
}
void CSPR_set_flag(const CPSRFLAGS f, const uint8_t value){
    uint32_t mask;
    if (value) {
        mask = f;
    }
    else {
        mask = !f;
    }
    CSPR_state = CSPR_state & mask;
}


/*
-------------------------

CSPR LOGIC REGION END

-------------------------

*/
