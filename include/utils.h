#ifndef UTILS_H
#define UTILS_H
#include "core.h"
#include "cpu.h"
int toUpper(char * s);


int ishexadecimal(char *);
int readhexadecimal(char * h, uint32_t *value);


int dumpRegisters(CPU* cpu);
#endif