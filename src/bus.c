#include "bus.h"
#include <stdio.h>
SystemMemoryMap DATA_BUS;

// Main Methods
byte_t* get_sector(address_t address){
    if (address < SYS_BIOS_END) {
        return (byte_t*)&DATA_BUS.bios;
    }
    else if (address >= BOARD_WRAM_START && address < BOARD_WRAM_END){
        return (byte_t*)&DATA_BUS.board_wram;
    }
    else if (address >= CHIP_WRAM_START && address < CHIP_WRAM_END) {
        return (byte_t*)&DATA_BUS.chip_wram;
    }
    else if (address >= IO_REGISTERS_START && address < IO_REGISTERS_END){
        return (byte_t*)&DATA_BUS.io_registers;
    }
    else if (address >= BG_PALETTE_RAM_START && address < BG_PALETTE_RAM_END){
        return (byte_t*)&DATA_BUS.bg_palette;
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
address_t get_sector_offset(byte_t * sector_ptr){
    if (sector_ptr == (byte_t*)&DATA_BUS.bios) {
        return SYSTEM_BIOS_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.board_wram){
        return BOARD_WRAM_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.chip_wram) {
        return CHIP_WRAM_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.io_registers){
        return IO_REGISTERS_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.bg_palette){
        return BG_PALETTE_RAM_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.vram){
        return VRAM_START;
    }
    else if (sector_ptr == (byte_t*)&DATA_BUS.oam){
        return OAM_START;
    }
    else {
        return -1;
    }
}

int write_byte(const address_t address, byte_t *data) {
    byte_t * sector_ptr = get_sector(address);
    if (!sector_ptr) return -1;
    uint32_t sector_offset = get_sector_offset(sector_ptr);
    sector_ptr[address-sector_offset] = *data;
    return 0;
}

int write_half_word (address_t address, half_word_t * data){
    byte_t * sector_ptr = get_sector(address);
    if (!sector_ptr) return -1;
    address_t sector_offset = get_sector_offset(sector_ptr);
    *(half_word_t *)(sector_ptr+address-sector_offset) = *data;

    return 0;
}
int write_word (address_t address, word_t *data){
    byte_t * sector_ptr = get_sector(address);
    if (!sector_ptr) return -1;
    address_t sector_offset = get_sector_offset(sector_ptr);
    *(word_t *)(sector_ptr+address-sector_offset) = *data;

    return 0;
}


int read_byte (address_t address, byte_t *data){
    byte_t * sector_ptr = get_sector(address);
    if (!sector_ptr) return -1;
    uint32_t sector_offset = get_sector_offset(sector_ptr);

    *data = sector_ptr[address-sector_offset];
    return 0;
}
int read_half_word (address_t address, half_word_t *data){
    byte_t * sector_ptr = get_sector(address);
    if (!sector_ptr) return -1;
    address_t sector_offset = get_sector_offset(sector_ptr);

    *data = *((half_word_t *)(sector_ptr + address-sector_offset));
    return 0;
}
int read_word (address_t address, word_t *data){
    byte_t * sector_ptr = (byte_t*)get_sector(address);
    if (!sector_ptr) return -1;
    uint32_t sector_offset = get_sector_offset(sector_ptr);

    *data = *((word_t *)(sector_ptr + address-sector_offset));
    return 0;
}


int clear_data_bus(){
  for(uint32_t i = 0; i<sizeof(SystemMemoryMap);i++){
    ((uint8_t *)(&DATA_BUS))[i] = 0;
  } 
  return 0;
}