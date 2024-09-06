#include "utils.h"

void setMemBlock(uint32_t * t, uint32_t size, uint32_t value){
    byte_t * bt = (uint8_t *)t;
    for(int i; i<size; ++i, ++bt){
        *bt = value;
    }
}