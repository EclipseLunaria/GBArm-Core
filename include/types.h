#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define AVAILABLE_REGISTERS 16

// type definitions
typedef uint8_t byte_t;
typedef uint16_t halfword_t;
typedef uint32_t word_t;
typedef uint32_t address_t;
typedef uint8_t flag_t;
typedef uint8_t reg_t;
typedef uint32_t instruction_t;

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


typedef struct Registers {
    uint32_t registers[AVAILABLE_REGISTERS];
    uint32_t fiq_registers[7];
    uint32_t svc_registers[2];
    uint32_t abt_registers[2];
    uint32_t irq_registers[2];
    uint32_t und_registers[2];
    uint32_t spsr_registers[5];
    uint32_t cpsr;
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
    address_t *PC;
    address_t *LR;
    uint32_t cpsr;

} CpuRegister;



#endif
