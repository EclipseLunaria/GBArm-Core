#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "internal/memory_bus.h"
#include "test_macros.h"
#include "types.h"

void test_memory_bus_init() {
    MemoryBus bus;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &bus);
    CU_ASSERT_EQUAL(bus.sector_count, 2)
    CU_ASSERT_EQUAL(bus.buffer_length, 0x1FE)

    CU_ASSERT_EQUAL(bus.sectors[0].sector_size, 0xFF)
    CU_ASSERT_EQUAL(bus.sectors[0].start_address, 0x0)

    CU_ASSERT_EQUAL(bus.sectors[1].sector_size, 0xFF)
    CU_ASSERT_EQUAL(bus.sectors[1].start_address, 0xFF)
}

void test_out_of_order_sector_error() {
    MemoryBus bus;
    MemorySector sectors[] = {
        {.sector_size = 100, .start_address = 100},
        {.sector_size = 100, .start_address = 0},
    };

    CU_ASSERT_THROWS_ERROR(init_memory_bus(sectors, 2, &bus))
}
void test_out_of_32bit_range_error() {
    MemoryBus bus;
    MemorySector sectors[] = {
        {.sector_size = 0xFFFFFFFF, .start_address = 0xFF},
    };

    CU_ASSERT_THROWS_ERROR(init_memory_bus(sectors, 2, &bus))
}

void test_allocate_single_sector() {
    MemoryBus bus;

    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        // {.sector_size = 0xFF, .start_address = 0xFF},
    };
    init_memory_bus(sectors, 1, &bus);

    CU_ASSERT_EQUAL(bus.buffer_length, 0xFF)
    CU_ASSERT_EQUAL(bus.memory_buffer[0], 0);
    destroy_memory_bus(&bus);
}

void test_allocate_two_sectors() {
    MemoryBus bus;

    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };
    init_memory_bus(sectors, 2, &bus);
    printf("SIZE %x", bus.buffer_length);
    CU_ASSERT_EQUAL(bus.buffer_length, 0x1FE)
    CU_ASSERT_EQUAL(bus.sectors[1].sector_buffer, &bus.memory_buffer[0xFF])
    destroy_memory_bus(&bus);
}

/*
TEST REGION: MEMORY WRITE OPERATIONS
*/

void test_memory_write_byte_first_sector() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFFF},
    };
    init_memory_bus(sectors, 2, &memory);

    memory_write_byte(0xF, 0xFF, &memory);

    CU_ASSERT_EQUAL(memory.memory_buffer[0xFF], 0xFF)
    CU_ASSERT_EQUAL(memory.sectors[0].sector_buffer[0xFF], 0xFF)
    destroy_memory_bus(&memory);
}

void test_get_memory_sector() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };
    init_memory_bus(sectors, 2, &memory);

    MemorySector* sector_one = get_memory_sector(0xF, &memory);
    MemorySector* sector_two = get_memory_sector(0xFF, &memory);
    CU_ASSERT_EQUAL(sector_one, &memory.sectors[0])
    CU_ASSERT_EQUAL(sector_two, &memory.sectors[1])

    destroy_memory_bus(&memory);
}

void test_get_memory_sector_non_zero_sector_start() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0xFF},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };
    init_memory_bus(sectors, 2, &memory);

    MemorySector* actual = get_memory_sector(0x0, &memory);
    CU_ASSERT_PTR_NULL(actual)
    destroy_memory_bus(&memory);
}
void test_write_byte_invalid_sector() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0x1FE},
    };
    init_memory_bus(sectors, 2, &memory);
    CU_ASSERT_THROWS_ERROR(memory_write_byte(0xFF, 0x69, &memory))
    CU_ASSERT_THROWS_ERROR(memory_write_byte(0xFFFF, 0x69, &memory))

    destroy_memory_bus(&memory);
}
void test_write_byte_sector_one() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };
    init_memory_bus(sectors, 2, &memory);
    memory_write_byte(0x4, 0x69, &memory);
    memory_write_byte(0x100, 0x69, &memory);

    CU_ASSERT_EQUAL(memory.sectors[0].sector_buffer[4], 0x69)
    CU_ASSERT_EQUAL(memory.sectors[1].sector_buffer[1], 0x69)

    destroy_memory_bus(&memory);
}
void test_write_halfword_invalid_sector() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0x1FE},
    };
    init_memory_bus(sectors, 2, &memory);
    CU_ASSERT_THROWS_ERROR(memory_write_halfword(0xFF, 0x69, &memory));
    CU_ASSERT_THROWS_ERROR(memory_write_halfword(0xFE, 0x69, &memory));
    destroy_memory_bus(&memory);
}

void test_write_halfword() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF00},
    };
    init_memory_bus(sectors, 2, &memory);
    memory_write_halfword(0x4, 0xFFF, &memory);
    memory_write_halfword(0xFF00, 0xFFF, &memory);

    CU_ASSERT_EQUAL(*(halfword_t*)&memory.sectors[0].sector_buffer[4], 0xFFF)
    CU_ASSERT_EQUAL(*(halfword_t*)&memory.sectors[1].sector_buffer[0], 0xFFF)

    destroy_memory_bus(&memory);
}

void test_write_word_invalid_sector() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0x1FE},
    };
    init_memory_bus(sectors, 2, &memory);
    for (int i = 0; i < 4; ++i) {
        CU_ASSERT_THROWS_ERROR(memory_write_word(0xFF - i, 0x69, &memory));
    }
    destroy_memory_bus(&memory);
}

void test_write_word() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF00},
    };
    init_memory_bus(sectors, 2, &memory);
    memory_write_word(0x4, 0xFFFFF, &memory);
    memory_write_word(0xFF00, 0xFFFFF, &memory);

    CU_ASSERT_EQUAL(*(word_t*)&memory.sectors[0].sector_buffer[4], 0xFFFFF)
    CU_ASSERT_EQUAL(*(word_t*)&memory.sectors[1].sector_buffer[0], 0xFFFFF)

    destroy_memory_bus(&memory);
}

void test_read_byte() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    memory.sectors[0].sector_buffer[4] = 0x55;
    memory.sectors[1].sector_buffer[1] = 0x44;

    byte_t actual1, actual2;

    memory_read_byte(0x4, &memory, &actual1);
    memory_read_byte(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x55)
    CU_ASSERT_EQUAL(actual2, 0x44)
}
void test_read_halfword() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    *(halfword_t*)&memory.sectors[0].sector_buffer[4] = 0x5555;
    *(halfword_t*)&memory.sectors[1].sector_buffer[1] = 0x4444;

    halfword_t actual1, actual2;

    memory_read_halfword(0x4, &memory, &actual1);
    memory_read_halfword(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x5555)
    CU_ASSERT_EQUAL(actual2, 0x4444)
}
void test_read_word() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    *(word_t*)&memory.sectors[0].sector_buffer[4] = 0x555555;
    *(word_t*)&memory.sectors[1].sector_buffer[1] = 0x444444;

    word_t actual1, actual2;

    memory_read_word(0x4, &memory, &actual1);
    memory_read_word(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x555555)
    CU_ASSERT_EQUAL(actual2, 0x444444)
}

void test_read_byte_invalid_address() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);
    byte_t b;
    CU_ASSERT_THROWS_ERROR(memory_read_byte(0xFFFF, &memory, &b))
}
void test_read_halfword_invalid_address() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);
    halfword_t h;
    CU_ASSERT_THROWS_ERROR(memory_read_halfword(0xFFFF, &memory, &h))
}
void test_read_word_invalid_address() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);
    word_t w;
    CU_ASSERT_THROWS_ERROR(memory_read_word(0xFFFF, &memory, &w))
}

void test_write_read_byte() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    memory.sectors[0].sector_buffer[4] = 0x55;
    memory.sectors[1].sector_buffer[1] = 0x44;

    byte_t actual1, actual2;

    memory_read_byte(0x4, &memory, &actual1);
    memory_read_byte(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x55)
    CU_ASSERT_EQUAL(actual2, 0x44)
}
void test_write_read_halfword() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    memory_write_halfword(0x4, 0x555, &memory);
    memory_write_halfword(0x100, 0x444, &memory);

    halfword_t actual1, actual2;

    memory_read_halfword(0x4, &memory, &actual1);
    memory_read_halfword(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x555)
    CU_ASSERT_EQUAL(actual2, 0x444)
}
void test_write_read_word() {
    MemoryBus memory;
    MemorySector sectors[] = {
        {.sector_size = 0xFF, .start_address = 0x0},
        {.sector_size = 0xFF, .start_address = 0xFF},
    };

    init_memory_bus(sectors, 2, &memory);

    memory_write_word(0x4, 0x55555, &memory);
    memory_write_word(0x100, 0x44444, &memory);

    word_t actual1, actual2;

    memory_read_word(0x4, &memory, &actual1);
    memory_read_word(0x100, &memory, &actual2);

    CU_ASSERT_EQUAL(actual1, 0x55555)
    CU_ASSERT_EQUAL(actual2, 0x44444)
}

int add_memory_bus_tests() {
    CU_pSuite suite = CU_add_suite("Long Multiply Tests", 0, 0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_memory_bus_init)

    // Test initialization
    ADD_TEST(test_out_of_order_sector_error)
    ADD_TEST(test_out_of_32bit_range_error)
    ADD_TEST(test_allocate_single_sector)
    ADD_TEST(test_allocate_two_sectors)

    // test helper functions
    ADD_TEST(test_get_memory_sector)
    ADD_TEST(test_get_memory_sector_non_zero_sector_start)

    // test write operations
    ADD_TEST(test_write_byte_invalid_sector)
    ADD_TEST(test_write_byte_sector_one)

    ADD_TEST(test_write_halfword_invalid_sector)
    ADD_TEST(test_write_halfword)

    ADD_TEST(test_write_word_invalid_sector)
    ADD_TEST(test_write_word)

    // test read operations
    ADD_TEST(test_read_byte)
    ADD_TEST(test_read_halfword)
    ADD_TEST(test_read_word)

    ADD_TEST(test_read_byte_invalid_address)
    ADD_TEST(test_read_halfword_invalid_address)
    ADD_TEST(test_read_word_invalid_address)

    ADD_TEST(test_write_read_byte)
    ADD_TEST(test_write_read_halfword)
    ADD_TEST(test_write_read_word)

    return CUE_SUCCESS;
}
