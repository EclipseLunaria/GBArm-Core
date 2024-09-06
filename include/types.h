#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <string.h>
typedef uint8_t byte_t;
typedef uint16_t half_word_t;
typedef uint32_t word_t;
typedef uint32_t address_t;

//Current Program Status Register 
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



#endif