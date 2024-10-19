#ifndef MEMORY_BUS_H
#define MEMORY_BUS_H
#include "error.h"
#include "core.h"



int init_memory_bus(MemorySector sectors[], uint8_t n, MemoryBus* memory_bus);
int destroy_memory_bus(MemoryBus* memory_bus);

int memory_write_byte(address_t address, byte_t byte, MemoryBus* memory_bus);
int memory_write_halfword(address_t address, halfword_t halfword, MemoryBus* memory_bus);
int memory_write_word(address_t address, word_t word, MemoryBus* memory_bus);

int memory_read_byte(address_t address, MemoryBus* memory_bus, byte_t* byte);
int memory_read_halfword(address_t address, MemoryBus* memory_bus, halfword_t* halfword);
int memory_read_word(address_t address, MemoryBus* memory_bus, word_t* word);

// helpers

MemorySector* get_memory_sector(address_t address, MemoryBus* memory_bus);
#endif
