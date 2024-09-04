#include "types.h"

// Register Info: https://problemkaputt.de/gbatek-arm-cpu-register-set.htm

typedef struct SystemRegisters {
    
    uint32_t r[13]; //General Purpose Registers
    uint32_t stackPointer; // Stack Pointers
    uint32_t linkRegister; //Link Register
    uint32_t programCounter;
    uint32_t CPSR; 
} SystemRegisters;

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
} CPSRFLAGS;
extern uint32_t CSPR_state;
uint8_t CSPR_get_flag(CPSRFLAGS f);
void CSPR_set_flag(CPSRFLAGS f, uint8_t value);
