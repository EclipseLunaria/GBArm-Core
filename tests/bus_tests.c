#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../include/bus.h"
#include "types.h"

// #include "../src/bus.c"

// Forward Declares
byte_t* get_sector(address_t address);
address_t getSectorOffset(byte_t* sectorPtr);

// Tests
void test_clear_bus_data(void)
{
    DATA_BUS.bios[0] = 123;
    DATA_BUS.bios[5] = 222;
    DATA_BUS.chip_wram[3] = (uint8_t)333;
    CU_ASSERT_EQUAL(123, DATA_BUS.bios[0]);
    CU_ASSERT_EQUAL(222, DATA_BUS.bios[5]);
    CU_ASSERT_EQUAL((uint8_t)333, DATA_BUS.chip_wram[3]);
    clear_data_bus();
    CU_ASSERT_EQUAL(0, DATA_BUS.bios[0]);
    CU_ASSERT_EQUAL(0, DATA_BUS.bios[5]);
    CU_ASSERT_EQUAL(0, DATA_BUS.chip_wram[3]);
}

// TEST READ/WRITE BYTE
void test_write_byte_to_bios()
{
    byte_t byte = 211;
    write_byte(3, &byte);
    CU_ASSERT_EQUAL(211, DATA_BUS.bios[3]);
}

void test_write_byte_to_board_wram()
{
    uint8_t byte = 232;
    write_byte(BOARD_WRAM_START + 52, &byte);
    CU_ASSERT_EQUAL(232, DATA_BUS.board_wram[52]);
}

void test_write_byte_to_vram()
{
    uint8_t byte = 232;
    write_byte(0x06000000 + 52, &byte);
    CU_ASSERT_EQUAL(232, DATA_BUS.board_wram[52]);
}

void test_read_byte_to_bios()
{
    byte_t byte = 111;
    DATA_BUS.bios[8] = byte;
    read_byte(8, &byte);
    CU_ASSERT_EQUAL(111, byte);
}
void test_read_byte_to_board_wram()
{
    byte_t byte = 44;
    DATA_BUS.board_wram[8] = byte;
    read_byte(BOARD_WRAM_START + 8, &byte);
    CU_ASSERT_EQUAL(44, byte);
}

void test_read_write_halfword_to_bios()
{
    halfword_t input = 444;
    write_half_word(10, &input);
    halfword_t output;
    read_half_word(10, &output);
    CU_ASSERT_EQUAL(output, input)
}

void test_read_write_word_to_bios()
{
    word_t input = 4445755;
    write_word(10, &input);
    word_t output;
    read_word(10, &output);
    CU_ASSERT_EQUAL(output, input)
}

// helper tests

void test_get_valid_sector_impl()
{
    const address_t bios_sector_location = 0x02FFF;
    const address_t board_sector_location = 0x02000100;
    const address_t chip_sector_location = 0x03000200;
    const address_t io_register_location = 0x04000010;
    const address_t bg_palette_location = 0x05000020;
    const address_t vram_location = 0x06000300;
    const address_t oam_location = 0x07000200;
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.bios, get_sector(bios_sector_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.board_wram, get_sector(board_sector_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.chip_wram, get_sector(chip_sector_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.io_registers, get_sector(io_register_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.bg_palette, get_sector(bg_palette_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.vram, get_sector(vram_location))
    CU_ASSERT_PTR_EQUAL(&DATA_BUS.oam, get_sector(oam_location))
}

void test_get_invalid_sector_impl()
{
    const address_t bad_bios_sector_location = 0x05000;
    const address_t bad_board_sector_location = 0x2EEEEEE;
    const address_t bad_chip_sector_location = 0x03FEFFFF;
    const address_t bad_io_register_location = 0x04FFEFFF;

    CU_ASSERT_PTR_NULL(get_sector(bad_bios_sector_location));
    CU_ASSERT_PTR_NULL(get_sector(bad_board_sector_location));
    CU_ASSERT_PTR_NULL(get_sector(bad_chip_sector_location));
    CU_ASSERT_PTR_NULL(get_sector(bad_io_register_location));
}

// Setup Teardown
int setup(void)
{
    clear_data_bus();
    return 0;
}

// Teardown function (runs after each test)
int teardown(void)
{
    clear_data_bus();
    return 0;
}

int add_bus_tests()
{
    CU_pSuite suite = CU_add_suite("Data Bus Tests", setup, teardown);

    if (suite == NULL) return CU_get_error();

    // Add Tests
    if (NULL == CU_add_test(suite, "test clearing data bus", test_clear_bus_data))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test write byte to bios", test_write_byte_to_bios))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test write byte to board wram", test_write_byte_to_board_wram))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test write byte to vram sector", test_write_byte_to_vram))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test read byte to board bios", test_read_byte_to_bios))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test read byte to board wram", test_read_byte_to_bios))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test read write half-word in bios", test_read_write_halfword_to_bios))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test read write word in bios", test_read_write_word_to_bios))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test get sector function for each valid sector", test_get_valid_sector_impl))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test get sector function for each invalid sector", test_get_invalid_sector_impl))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    return CUE_SUCCESS;
}