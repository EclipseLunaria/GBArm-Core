#include "utils.h"

uint32_t sLen(char * s){
    uint32_t i;
    while (*s) {
        ++i;
        ++s;
    }
    return i;
}

int toUpper(char * s){
    char * c = s;
    for (int i = 0; i < strlen(s); ++i){
        if (*c >= 'a' && *c <= 'z') {
            *c = *c - 'a' + 'A';
        }
        c++;
    }

    return 0;
}