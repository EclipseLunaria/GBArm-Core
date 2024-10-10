#ifndef CORE_H
#define CORE_H

#include <assert.h>
#include <constants.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "memory_bus.h"
#include "types.h"

#define PRINTX(x) printf("\n #x: %x\n", x)

#define AVAILABLE_REGISTERS 16

#define KB 1024

typedef struct CPSR {
    unsigned mode_bits : 5;   // Mode Bits
    unsigned T : 1;           // State Bit       (0=ARM, 1=THUMB) - Do not change manually!
    unsigned F : 1;           // FIQ disable     (0=Enable, 1=Disable)
    unsigned I : 1;           // IRQ disable     (0=Enable, 1=Disable)
    unsigned A : 1;           // Abort disable   (1=Disable Imprecise Data Aborts) (ARM11 only)
    unsigned E : 1;           // Endian          (... Big endian)
    unsigned reserved2 : 14;  // Reserved        (For future use) - Do not change manually!
    unsigned J : 1;           // Jazelle Mode    (1=Jazelle Bytecode instructions) (if supported)
    unsigned reserved1 : 2;   // Reserved        (For future use) - Do not change manually!
    unsigned Q : 1;           // Sticky Overflow (1=Sticky Overflow, ARMv5TE and up only)
    unsigned V : 1;           // Overflow Flag   (0=No Overflow, 1=Overflow)
    unsigned C : 1;           // Carry Flag      (0=Borrow/No Carry, 1=Carry/No Borrow)
    unsigned Z : 1;           // Zero Flag       (0=Not Zero, 1=Zero)
    unsigned N : 1;           // Sign Flag       (0=Not Signed, 1=Signed)
} CPSR;

typedef struct BS_FLAGS {
    uint8_t unused : 3, Is_arithmetic : 1, Z : 1, N : 1, C : 1, V : 1;

} BS_FLAGS;

typedef struct SystemMemoryMap {
    byte_t bios[16 * KB];
    byte_t board_wram[256 * KB];
    byte_t chip_wram[32 * KB];
    byte_t io_registers[0x03FE];
    byte_t bg_palette[1 * KB];
    byte_t vram[96 * KB];
    byte_t oam[1 * KB];
} SystemMemoryMap;

typedef struct Registers {
    uint32_t registers[AVAILABLE_REGISTERS];
    uint32_t fiq_registers[7];
    uint32_t svc_registers[2];
    uint32_t abt_registers[2];
    uint32_t irq_registers[2];
    uint32_t und_registers[2];
    uint32_t spsr_registers[5];
    uint32_t cpsr;
    CPSR *p_cpsr;
} Registers;

typedef struct RegisterSet {
    uint32_t *p_registers[AVAILABLE_REGISTERS];
    uint32_t *p_spsr;
} RegisterSet;

typedef struct CpuRegister {
    Registers register_data;
    RegisterSet register_sets[6];
    RegisterSet *current_registers;
    uint8_t current_mode;
    uint32_t *PC;
    uint32_t *LR;
    uint32_t cpsr;

} CpuRegister;

typedef struct CPU {
    MemoryBus memory;
    CpuRegister registers;
    uint32_t loaded_instruction;
    uint64_t clock_cycles;
    uint16_t sleep_cycles;
    CPSR *CPSR;
} CPU;

#endif