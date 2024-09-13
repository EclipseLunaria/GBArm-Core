#include "utils.h"

uint32_t sLen(char * s){
    uint32_t i;
    while (*s) {
        ++i;
        ++s;
    }
    return i;
}

int toLower(char * s){
    char * c = s;
    for (int i = 0; i < strlen(s); ++i){
        if (*c >= 'A' && *c <= 'Z') {
            *c = *c - 'A' + 'a';
        }
        c++;
    }

    return 0;
}