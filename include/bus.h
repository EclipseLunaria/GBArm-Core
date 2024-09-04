#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "types.h"

#define KB 1024
#define SYSTEM_BIOS_SIZE 16 * KB
#define SYS_BIOS_OFFSET 0
#define BOARD_WRAM_SIZE 256 * KB
#define BOARD_WRAM_OFFSET 0x02000000
#define CHIP_WRAM_SIZE 32 *KB
#define CHIP_WRAM_OFFSET  0x03000000
#define IO_REGISTERS_SIZE 0x03FE
#define IO_REGISTERS_OFFSET 0x04000000


typedef struct SystemMemoryMap {
   byte_t bios[16*1024];
   byte_t boardWRAM[256*1024];
   byte_t chipWRAM[32*1024];
   byte_t ioRegisters[0x3FE];
   byte_t errorFlag;
} SystemMemoryMap;


extern SystemMemoryMap DATA_BUS;

int writeByte (address_t address, byte_t *data);
int writeHalfWord (address_t address, half_word_t *data);
int writeWord (address_t address, word_t *data);

int readByte (address_t address, byte_t * data);
int readHalfWord (address_t address, half_word_t *data);
int readWord (address_t address, word_t *data);

int clearDataBus();

#endif