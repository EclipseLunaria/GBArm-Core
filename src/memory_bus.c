#include "memory_bus.h"

int init_memory_bus(MemorySector sectors[], uint8_t n, MemoryBus* memory_bus) {
    if (n > MAX_SECTORS) {
        THROW_ERROR("Invalid number of sectors: %d, exceeds %d sectors", n, MAX_SECTORS)
    }
    memset(memory_bus, 0, sizeof(MemoryBus));
    size_t current_size = 0;
    address_t last_address = 0;
    // validate sectors in order and do not overlap
    for (int i = 0; i < n; ++i) {
        if (sectors[i].start_address < last_address) {
            THROW_ERROR("Sectors Must Be in order")
        }

        if (sectors[i].start_address > sectors[i].start_address + sectors[i].sector_size) {
            THROW_ERROR("Sector Does not fit in 32 bit address bounds")
        }
        current_size += sectors[i].sector_size;
        last_address = sectors[i].start_address + sectors[i].sector_size;
    }

    // allocate memory for sectors as single array
    memory_bus->buffer_length = current_size;
    memory_bus->memory_buffer = (byte_t*)malloc(memory_bus->buffer_length);
    memset(memory_bus->memory_buffer, 0, memory_bus->buffer_length);

    byte_t* pbuffer = memory_bus->memory_buffer;
    for (int i = 0; i < n; ++i) {
        // investigate for test
        MemorySector current_sector = sectors[i];
        current_sector.sector_buffer = pbuffer;
        memcpy(&memory_bus->sectors[i], &current_sector, sizeof(MemorySector));
        pbuffer += current_sector.sector_size;
    }
    memory_bus->sector_count = n;
    return 0;
}

int destroy_memory_bus(MemoryBus* memory_bus) {
    if (memory_bus->memory_buffer) {
        free(memory_bus->memory_buffer);
    }
    return 0;
}

int memory_write_byte(address_t address, byte_t byte, MemoryBus* memory_bus) {
    MemorySector* psector = get_memory_sector(address, memory_bus);
    if (!psector || psector->start_address + psector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }

    psector->sector_buffer[address - psector->start_address] = byte;
    return 0;
}
int memory_write_halfword(address_t address, halfword_t halfword, MemoryBus* memory_bus) {
    MemorySector* psector = get_memory_sector(address, memory_bus);
    if (!psector || psector->start_address + psector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }
    printf("\nVALUE: %x %x %x\n", address, psector->start_address, psector->sector_size);
    if (address - psector->start_address > psector->sector_size - 2) {
        THROW_ERROR("Insufficient addressings space for halfword")
    }

    *(halfword_t*)&psector->sector_buffer[address - psector->start_address] = halfword;
    return 0;
}
int memory_write_word(address_t address, word_t word, MemoryBus* memory_bus) {
    MemorySector* psector = get_memory_sector(address, memory_bus);
    if (!psector || psector->start_address + psector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }
    if (address - psector->start_address > psector->sector_size - 4) {
        THROW_ERROR("Insufficient addressings space for word")
    }

    *(word_t*)&psector->sector_buffer[address - psector->start_address] = word;
    return 0;
}

int memory_read_byte(address_t address, MemoryBus* memory_bus, byte_t* byte) {
    MemorySector* sector = get_memory_sector(address, memory_bus);
    if (!sector || sector->start_address + sector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }

    *byte = sector->sector_buffer[address - sector->start_address];
    return 0;
}
int memory_read_halfword(address_t address, MemoryBus* memory_bus, halfword_t* halfword) {
    MemorySector* sector = get_memory_sector(address, memory_bus);
    if (!sector || sector->start_address + sector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }

    *halfword = *(halfword_t*)&sector->sector_buffer[address - sector->start_address];
    return 0;
}
int memory_read_word(address_t address, MemoryBus* memory_bus, word_t* word) {
    MemorySector* sector = get_memory_sector(address, memory_bus);
    if (!sector || sector->start_address + sector->sector_size <= address) {
        THROW_ERROR("Attempting to write to inaccessable memory location: $%x, check the allocated sectors", address);
    }

    *word = *(word_t*)&sector->sector_buffer[address - sector->start_address];
    return 0;
}

// helpers

MemorySector* get_memory_sector(address_t address, MemoryBus* memory_bus) {
    MemorySector* current_sector = NULL;

    for (int i = 0; i < memory_bus->sector_count; ++i) {
        if (memory_bus->sectors[i].start_address <= address) {
            current_sector = &memory_bus->sectors[i];
        }
    }
    return current_sector;
}
