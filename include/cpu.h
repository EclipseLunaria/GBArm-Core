#ifndef CPU_H
#define CPU_H

#include "core.h"
#include "types.h"

#include "bus.h"
#include "registers.h"
#include <stdio.h>



typedef enum CPSRFLAGS {
    N = (1 << 31),          // Sign Flag      (0=Not Signed, 1=Signed)
    Z = (1 << 30),          //Zero Flag       (0=Not Zero, 1=Zero)        
    C = (1 << 29),          //Carry Flag      (0=Borrow/No Carry, 1=Carry/No Borrow)
    V = (1 << 28),          //Overflow Flag   (0=No Overflow, 1=Overflow)
    Q = (1 << 27),          //Sticky Overflow (1=Sticky Overflow, ARMv5TE and up only)
    J = (1 << 24),          //Jazelle Mode    (1=Jazelle Bytecode instructions) (if supported)
    E = (1 << 9),           //Endian          (... Big endian)                  
    A = (1 << 8),           //Abort disable   (1=Disable Imprecise Data Aborts) (ARM11 only)
    I = (1 << 7),           //IRQ disable     (0=Enable, 1=Disable)
    F = (1 << 6),           //FIQ disable     (0=Enable, 1=Disable)
    T = (1 << 5)            // The T Bit signalizes the current state of the CPU (0=ARM, 1=THUMB), this bit should never be changed manually - instead, changing between ARM and THUMB state must be done by BX instructions.
} CPSRFLAGS;

int initCpu(CPU *cpu);
int clockCpu(CPU *cpu);

uint8_t evaluate_cond(uint8_t opcode, const uint32_t CPSR_state);

#endif