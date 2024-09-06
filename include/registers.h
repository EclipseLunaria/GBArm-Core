#ifndef REGISTERS_H
#define REGISTERS_H
#include "types.h"
#define AVAILABLE_REGISTERS 16
typedef struct Registers {
    uint32_t registers[AVAILABLE_REGISTERS];
    uint32_t fiqRegisters[7];
    uint32_t svcRegisters[2];
    uint32_t abtRegisters[2];
    uint32_t irqRegisters[2];
    uint32_t undRegisters[2];
    uint32_t spsrRegisters[5];
    uint32_t cpsr;
    CPSR * pCpsr;
} Registers;

typedef struct RegisterSet {
    uint32_t *pRegisters[AVAILABLE_REGISTERS];
    uint32_t *pSpsr;
} RegisterSet;

typedef struct CpuRegister {
    Registers registerData;
    RegisterSet regSets[6];
    RegisterSet * curRegSet;
    uint8_t currentMode;
    uint32_t * PC;
    uint32_t cpsr;

} CpuRegister;

void dumpRegisterSet(RegisterSet regSet);

int initCpuRegisters(CpuRegister * cpuRegister);

int setMode(uint8_t mode, CpuRegister * cpuReg);
int readRegister(uint8_t regNum, CpuRegister * cpuReg, uint32_t *buf);
int writeRegister(uint8_t regNum, uint32_t value, CpuRegister * cpuReg);

#endif