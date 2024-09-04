#include "bus.h"
#include <stdio.h>
SystemMemoryMap DATA_BUS;

// Main Methods
byte_t* getSector(address_t address){
    if (address < SYSTEM_BIOS_SIZE) {
        return (byte_t*)&DATA_BUS.bios;
    }
    else if (address>=BOARD_WRAM_OFFSET && address<BOARD_WRAM_OFFSET+BOARD_WRAM_SIZE){
        return (byte_t*)&DATA_BUS.boardWRAM;
    }
    else if (address>=CHIP_WRAM_OFFSET && address<CHIP_WRAM_OFFSET+CHIP_WRAM_SIZE) {
        return (byte_t*)&DATA_BUS.chipWRAM;
    }
    else if (address>=IO_REGISTERS_OFFSET && address <IO_REGISTERS_OFFSET+IO_REGISTERS_SIZE){
        return (byte_t*)&DATA_BUS.ioRegisters;
    }
    else {
        return NULL;
    }
}
address_t getSectorOffset(byte_t * sectorPtr){
    if (sectorPtr == (byte_t*)&DATA_BUS.bios) {
        return SYS_BIOS_OFFSET;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.boardWRAM){
        return BOARD_WRAM_OFFSET;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.chipWRAM) {
        return CHIP_WRAM_OFFSET;
    }
    else if (sectorPtr == (byte_t*)&DATA_BUS.ioRegisters){
        return IO_REGISTERS_OFFSET;
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