#ifndef REGISTERS_H
#define REGISTERS_H
#include "types.h"
#include "core.h"

void dumpRegisterSet(RegisterSet regSet);

int initCpuRegisters(CpuRegister * cpuRegister);

int setMode(uint8_t mode, CpuRegister * cpuReg);
int readRegister(uint8_t regNum, CpuRegister * cpuReg, uint32_t *buf);
int writeRegister(uint8_t regNum, uint32_t value, CpuRegister * cpuReg);


#endif