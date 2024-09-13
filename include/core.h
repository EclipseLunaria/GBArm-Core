#ifndef CORE_H
#define CORE_H
#include <memory.h>
#include "types.h"

// define helper method macro for allowing for allowing for testing

#define PRINTX(x) printf("\n #x: %x\n", x)

#define AVAILABLE_REGISTERS 16

#define KB 1024

typedef struct CPSR {
    unsigned N:1, // Sign Flag      (0=Not Signed, 1=Signed)
    Z:1,          //Zero Flag       (0=Not Zero, 1=Zero)        
    C:1,          //Carry Flag      (0=Borrow/No Carry, 1=Carry/No Borrow)
    V:1,          //Overflow Flag   (0=No Overflow, 1=Overflow)
    Q:1,          //Sticky Overflow (1=Sticky Overflow, ARMv5TE and up only)
    reserved1:2,  //Reserved        (For future use) - Do not change manually!          
    J:1,          //Jazelle Mode    (1=Jazelle Bytecode instructions) (if supported)
    reserved2:14, //Reserved        (For future use) - Do not change manually!
    E:1,          //Endian          (... Big endian)                  
    A:1,          //Abort disable   (1=Disable Imprecise Data Aborts) (ARM11 only)
    I:1,          //IRQ disable     (0=Enable, 1=Disable)
    F:1,          //FIQ disable     (0=Enable, 1=Disable)
    T:1,          //State Bit       (0=ARM, 1=THUMB) - Do not change manually!
    mode_bits:5;  //Mode Bits   
} CPSR;

typedef struct BS_FLAGS {
    uint8_t
    unused:3,
    IsArithmetic:1,
    Z:1,
    N:1,
    C:1,
    V:1;

} BS_FLAGS;


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
    CPSR * CPSR;
} CPU;

#endif