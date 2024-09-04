#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "../include/bus.h"
// #include "../src/bus.c"

void test_clear_bus_data(void){
    DATA_BUS.bios[0] = 123;
    DATA_BUS.bios[5] = 222;
    DATA_BUS.chipWRAM[3] = (uint8_t)333;
    CU_ASSERT_EQUAL(123, DATA_BUS.bios[0]);
    CU_ASSERT_EQUAL(222, DATA_BUS.bios[5]);
    CU_ASSERT_EQUAL((uint8_t)333, DATA_BUS.chipWRAM[3]);
    clearDataBus();
    CU_ASSERT_EQUAL(0, DATA_BUS.bios[0]);
    CU_ASSERT_EQUAL(0, DATA_BUS.bios[5]);
    CU_ASSERT_EQUAL(0, DATA_BUS.chipWRAM[3]);
}

// TEST READ/WRITE BYTE
void test_write_byte_to_bios(){
    clearDataBus();
    byte_t byte = 211;
    writeByte(3,&byte);
    CU_ASSERT_EQUAL(211, DATA_BUS.bios[3]);
}

void test_write_byte_to_board_wram(){
    clearDataBus();
    uint8_t byte = 232;
    writeByte(BOARD_WRAM_OFFSET+52, &byte);
    CU_ASSERT_EQUAL(232, DATA_BUS.boardWRAM[52]);
}

void test_read_byte_to_bios(){
    clearDataBus();
    byte_t byte = 111;
    DATA_BUS.bios[8] = byte;
    readByte(8, &byte);
    CU_ASSERT_EQUAL(111, byte);
}
void test_read_byte_to_board_wram(){
    clearDataBus();
    byte_t byte = 44;
    DATA_BUS.boardWRAM[8] = byte;
    readByte(BOARD_WRAM_OFFSET+8, &byte);
    CU_ASSERT_EQUAL(44, byte);
}
void test_get_valid_sector_impl(){
    clearDataBus();
    const address_t bios_sector_location = 0x02FFF;
    const address_t board_sector_location = 0x02000100;
    const address_t chip_sector_location = 0x03000200;
    const address_t io_register_location = 0x04000010;
    CU_ASSERT_EQUAL(&DATA_BUS.bios, getSector(bios_sector_location));
    CU_ASSERT_EQUAL(&DATA_BUS.boardWRAM, getSector(board_sector_location));
    CU_ASSERT_EQUAL(&DATA_BUS.chipWRAM, getSector(chip_sector_location));
    CU_ASSERT_EQUAL(&DATA_BUS.ioRegisters, getSector(io_register_location));
}

void test_get_invalid_sector_impl() {
    const uint32_t bad_bios_sector_location = 0x05000;
    const uint32_t bad_board_sector_location = 0x2EEEEEE;
    const uint32_t bad_chip_sector_location = 0x03FEFFFF;
    const uint32_t bad_io_register_location = 0x04FFEFFF;

    CU_ASSERT_PTR_NULL(getSector(bad_bios_sector_location));
    CU_ASSERT_PTR_NULL(getSector(bad_board_sector_location));
    CU_ASSERT_PTR_NULL(getSector(bad_chip_sector_location));
    CU_ASSERT_PTR_NULL(getSector(bad_io_register_location));
}

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite pSuite = CU_add_suite("Bus_Suite",0,0);

    if(NULL==pSuite){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add Tests
    if (NULL == CU_add_test(pSuite, "test clearing data bus", test_clear_bus_data)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test write byte to bios", test_write_byte_to_bios)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test write byte to board wram", test_write_byte_to_board_wram)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "test read byte to board bios", test_read_byte_to_bios)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test read byte to board wram", test_read_byte_to_bios)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test get sector function for each valid sector", test_clear_bus_data)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test get sector function for each invalid sector", test_get_invalid_sector_impl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();

}