#include "bus.h"
#include <stdio.h>
    SystemMemoryMap DATA_BUS;

// Main Methods
void* getSector(uint32_t address){
    if (address < SYSTEM_BIOS_SIZE) {
        printf("ptr: %d\n", DATA_BUS.bios);
        return &DATA_BUS.bios;
    }
    else if (address>=BOARD_WRAM_OFFSET && address<BOARD_WRAM_OFFSET+BOARD_WRAM_SIZE){
        return &DATA_BUS.boardWRAM;
    }
    else if (address>=CHIP_WRAM_OFFSET && address<CHIP_WRAM_OFFSET+CHIP_WRAM_SIZE) {
        return &DATA_BUS.chipWRAM;
    }
    else if (address>=IO_REGISTERS_OFFSET && address <IO_REGISTERS_OFFSET+IO_REGISTERS_SIZE){
        return &DATA_BUS.ioRegisters;
    }
    else {
        return -1;
    }
}
uint32_t getSectorOffset(void * sectorPtr){
    printf("Board WRAM %d",&DATA_BUS.boardWRAM);
    if (sectorPtr == &DATA_BUS.bios) {
        return SYS_BIOS_OFFSET;
    }
    else if (sectorPtr == &DATA_BUS.boardWRAM){
        return BOARD_WRAM_OFFSET;
    }
    else if (sectorPtr == &DATA_BUS.chipWRAM) {
        return CHIP_WRAM_OFFSET;
    }
    else if (sectorPtr == &DATA_BUS.ioRegisters){
        return IO_REGISTERS_OFFSET;
    }
    else {
        return -1;
    }
}

int writeByte(const uint32_t address, uint8_t *data) {
    uint8_t * sectorPtr = (uint8_t *)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);
    sectorPtr[address-sectorOffset] = *data;
    return 0;
}

int writeHalfWord (uint32_t address, uint16_t * data){
    uint8_t * sectorPtr = (uint8_t *)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);
    *(uint16_t *)(sectorPtr+address-sectorOffset) = *data;

    return 0;
}
int writeWord (uint32_t address, uint32_t *data){
    uint8_t * sectorPtr = (uint8_t *)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = getSectorOffset(sectorPtr);
    *(uint32_t *)(sectorPtr+address-sectorOffset) = *data;

    return 0;
}


int readByte (uint32_t address, uint8_t *byte){
    uint8_t * sectorPtr = (uint8_t*)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = (uint8_t*)getSectorOffset(sectorPtr);

    *byte = sectorPtr[address-sectorOffset];
    return 0;
}
int readHalfWord (uint32_t address, uint16_t *halfWord){
    uint8_t * sectorPtr = (uint8_t*)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = (uint8_t*)getSectorOffset(sectorPtr);

    *halfWord = *((uint16_t *)(sectorPtr + address-sectorOffset));
    return 0;
}
int readWord (uint32_t address, uint32_t *word){
        uint8_t * sectorPtr = (uint8_t*)getSector(address);
    if (!sectorPtr) return -1;
    uint32_t sectorOffset = (uint8_t*)getSectorOffset(sectorPtr);

    *word = *((uint32_t *)(sectorPtr + address-sectorOffset));
    return 0;
}


int clearDataBus(){
  for(uint32_t i = 0; i<sizeof(SystemMemoryMap);i++){
    ((uint8_t *)(&DATA_BUS))[i] = 0;
  } 
}