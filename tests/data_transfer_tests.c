#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "cpu.h"
#include "instruction.h"
#include "test_macros.h"

void test_store_register_writeback_byte_data_up() {
    CPU cpu;
    init_cpu(&cpu);

    // flag_t I = 0;  // 0: register op, 1: immediate op
    flag_t P = 0;  // 0: post-index 1: pre-index
    flag_t U = 1;  // 1: up, 0: down
    flag_t B = 1;  // 0: word, 1: byte
    flag_t W = 1;  // writeback
    flag_t L = 0;  // 0: store, 1: load
    reg_t rn = 1;  // base register
    reg_t rd = 0;
    reg_t rm = 2;

    instruction_t instruction =
        0xE << 28 | 1 << 26 | P << 24 | U << 23 | B << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 | rm;
    // uint32_t rn_value = 0;
    // uint32_t rd_value = 0xEE;
    // uint32_t rm_value = 0xFF;

    write_register(rn, 0, &cpu.registers);
    write_register(rd, 0xEE, &cpu.registers);
    write_register(rm, 0x1, &cpu.registers);

    int status = SDT(instruction, &cpu);

    CU_ASSERT_EQUAL(status, 0)

    byte_t actual;
    memory_read_byte(0x0, &cpu.memory, &actual);
    CU_ASSERT_EQUAL(actual, 0xEE);
    uint32_t new_rn_value;
    read_register(rn, &cpu.registers, &new_rn_value);
    printf("new_rn_value: %x\n", new_rn_value);
    CU_ASSERT_EQUAL(new_rn_value, 1)
}

int add_data_transfer_tests() {
    CU_pSuite suite = CU_add_suite("Data Transfer Tests", 0, 0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_store_register_writeback_byte_data_up)
    return CUE_SUCCESS;
}