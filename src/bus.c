#include "bus.h"
#include <stdio.h>
SystemMemoryMap DATA_BUS;

// Main Methods
byte_t* getSector(address_t address){
    if (address < SYS_BIOS_END) {
        return (byte_t*)&DATA_BUS.bios;
    }
    else if (address >= BOARD_WRAM_START && address < BOARD_WRAM_END){
        return (byte_t*)&DATA_BUS.boardWRAM;
    }
    else if (address >= CHIP_WRAM_START && address < CHIP_WRAM_END) {
        return (byte_t*)&DATA_BUS.chipWRAM;
    }
    else if (address >= IO_REGISTERS_START && address < IO_REGISTERS_END){
        return (byte_t*)&DATA_BUS.ioRegisters;
    }
    else if (address >= BG_PALETTE_RAM_START && address < BG_PALETTE_RAM_END){
        return (byte_t*)&DATA_BUS.bgPalette;
    }
    else if (address >= VRAM_START && address < VRAM_END){
        return (byte_t*)&DATA_BUS.vram;
    }
    else if (address >= OAM_START && address < OAM_END){
        return (byte_t*)&DATA_BUS.oam;
    }
    else {
        return NULL;
    }
}
address_t getSectorOffset(byte_t * sectorPtr){
    if (sectorPtr == (byte_t*)&DATA_BUS.bios) {
        return SYSTEM_BIOS_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.boardWRAM){
        return BOARD_WRAM_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.chipWRAM) {
        return CHIP_WRAM_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.ioRegisters){
        return IO_REGISTERS_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.bgPalette){
        return BG_PALETTE_RAM_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.vram){
        return VRAM_START;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.oam){
        return OAM_START;
    }
    else {
        return -1;
    }
}

int writeByte(const address_t address, byte_t *data) {
    byte_t * sectorPtr = getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);
    sectorPtr[address-sectorOffset] = *data;
    return 0;
}

int writeHalfWord (address_t address, half_word_t * data){
    byte_t * sectorPtr = getSector(address);
    if (!sectorPtr) return -1;
    address_t sectorOffset = getSectorOffset(sectorPtr);
    *(half_word_t *)(sectorPtr+address-sectorOffset) = *data;

    return 0;
}
int writeWord (address_t address, word_t *data){
    byte_t * sectorPtr = getSector(address);
    if (!sectorPtr) return -1;
    address_t sectorOffset = getSectorOffset(sectorPtr);
    *(word_t *)(sectorPtr+address-sectorOffset) = *data;

    return 0;
}


int readByte (address_t address, byte_t *data){
    byte_t * sectorPtr = getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);

    *data = sectorPtr[address-sectorOffset];
    return 0;
}
int readHalfWord (address_t address, half_word_t *data){
    byte_t * sectorPtr = getSector(address);
    if (!sectorPtr) return -1;
    address_t sectorOffset = getSectorOffset(sectorPtr);

    *data = *((half_word_t *)(sectorPtr + address-sectorOffset));
    return 0;
}
int readWord (address_t address, word_t *data){
    byte_t * sectorPtr = (byte_t*)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);

    *data = *((word_t *)(sectorPtr + address-sectorOffset));
    return 0;
}


int clearDataBus(){
  for(uint32_t i = 0; i<sizeof(SystemMemoryMap);i++){
    ((uint8_t *)(&DATA_BUS))[i] = 0;
  } 
  return 0;
}