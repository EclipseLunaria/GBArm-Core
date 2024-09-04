#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "types.h"

#define KB 1024

#define SYSTEM_BIOS_START 0
#define SYS_BIOS_END SYSTEM_BIOS_START + 16 * KB

#define BOARD_WRAM_START 0x02000000
#define BOARD_WRAM_END BOARD_WRAM_START + 256 * KB


#define CHIP_WRAM_START 0x03000000
#define CHIP_WRAM_END CHIP_WRAM_START + 32 *KB

#define IO_REGISTERS_SIZE 0x03FE
#define IO_REGISTERS_START 0x04000000
#define IO_REGISTERS_END IO_REGISTERS_START + IO_REGISTERS_SIZE


// Internal Display Memory


typedef struct SystemMemoryMap {
   byte_t bios[16*KB];
   byte_t boardWRAM[256*KB];
   byte_t chipWRAM[32*KB];
   byte_t ioRegisters[IO_REGISTERS_SIZE];
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