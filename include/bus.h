#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "types.h"
#include "core.h"


#define SYSTEM_BIOS_START 0
#define SYS_BIOS_END SYSTEM_BIOS_START + 16 * KB

#define BOARD_WRAM_START 0x02000000
#define BOARD_WRAM_END BOARD_WRAM_START + 256 * KB


#define CHIP_WRAM_START 0x03000000
#define CHIP_WRAM_END CHIP_WRAM_START + 32 *KB

#define IO_REGISTERS_SIZE 0x03FE
#define IO_REGISTERS_START 0x04000000
#define IO_REGISTERS_END IO_REGISTERS_START + IO_REGISTERS_SIZE

#define BG_PALETTE_RAM_START 0x05000000
#define BG_PALETTE_RAM_END 0x050003FF

#define VRAM_START 0x06000000
#define VRAM_END 0x06017FFF   

// OBJ Attributes
#define OAM_START 0x07000000
#define OAM_END 0x070003FF

// Internal Display Memory



extern SystemMemoryMap DATA_BUS;

int writeByte (address_t address, byte_t *data);
int writeHalfWord (address_t address, half_word_t *data);
int writeWord (address_t address, word_t *data);

int readByte (address_t address, byte_t * data);
int readHalfWord (address_t address, half_word_t *data);
int readWord (address_t address, word_t *data);

int clearDataBus();

#endif