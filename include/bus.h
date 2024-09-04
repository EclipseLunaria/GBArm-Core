#ifndef BUS_H
#define BUS_H

#include <stdint.h>
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
   uint8_t bios[16*1024];
   uint8_t boardWRAM[256*1024];
   uint8_t chipWRAM[32*1024];
   uint8_t ioRegisters[0x3FE];
   uint8_t errorFlag;
} SystemMemoryMap;


extern SystemMemoryMap DATA_BUS;

int writeByte (uint32_t address, uint8_t *data);
int writeHalfWord (uint32_t address, uint16_t *data);
int writeWord (uint32_t address, uint32_t *data);

int readByte (uint32_t address, uint8_t * byte);
int readHalfWord (uint32_t address, uint16_t *halfWord);
int readWord (uint32_t address, uint32_t *word);

#endif