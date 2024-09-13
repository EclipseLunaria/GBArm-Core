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

int ishexadecimal(char * h){
    if ( strlen(h) <= 2 || strncmp(h, "0x",2)) return 0;

    for(int i = 2; i<strlen(h); ++i){
        if (!isdigit(h[i]) && (toupper(h[i]) < 'A' || toupper(h[i]) >'F')) return 0;
    }
    return 1;
}

int readhexadecimal(char * h, uint32_t *value){
    if (!strncmp(h, "0x",2)) h+=2;
    int result = sscanf(h, "%x", value);
    return result;
}
