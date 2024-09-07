#ifndef CORE_H
#define CORE_H

#include "types.h"
#define AVAILABLE_REGISTERS 16

#define KB 1024


typedef struct SystemMemoryMap {
   byte_t bios[16*KB];
   byte_t boardWRAM[256*KB];
   byte_t chipWRAM[32*KB];
   byte_t ioRegisters[0x03FE];
   byte_t bgPalette[1*KB];
   byte_t vram[96*KB];
   byte_t oam[1*KB];
   byte_t errorFlag;
} SystemMemoryMap;


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
    uint32_t * LR;
    uint32_t cpsr;

} CpuRegister;


typedef struct CPU {
    SystemMemoryMap ram;
    CpuRegister registers;
    uint32_t loadedInstruction;
    uint64_t clockCycle;
    uint16_t sleepCycles;
} CPU;

#endif