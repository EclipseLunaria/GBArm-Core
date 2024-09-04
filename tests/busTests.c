#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "../include/bus.h"

void test_clear_bus_data(void){
    DATA_BUS.bios[0] = 123;
    DATA_BUS.bios[5] = 222;
    DATA_BUS.chipWRAM[3] = (uint8_t)333;
    printf("data 5: %d",DATA_BUS.chipWRAM[3]);
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
    uint8_t byte = 211;
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
    uint8_t byte = 111;
    DATA_BUS.bios[8] = byte;
    readByte(8, &byte);
    CU_ASSERT_EQUAL(111, byte);
}
void test_read_byte_to_board_wram(){
    clearDataBus();
    uint8_t byte = 44;
    DATA_BUS.boardWRAM[8] = byte;
    readByte(BOARD_WRAM_OFFSET+8, &byte);
    CU_ASSERT_EQUAL(44, byte);
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

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();

}