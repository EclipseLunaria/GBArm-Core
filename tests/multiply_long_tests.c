#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "cpu.h"
#include "multiply.h"
#include "test_macros.h"

void test_correct_long_multiply_instruction_set_bits() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction
    uint8_t cond = 0xE;

    // set registers and flags
    flag_t U = 0;
    flag_t A = 0;
    flag_t S = 0;
    reg_t rd_hi = 0;
    reg_t rd_lo = 2;
    reg_t rs = 0;
    reg_t rm = 1;
    instruction_t instruction = cond << 28 | U << 22 | A << 21 | S << 20 |
                                rd_hi << 16 | rd_lo << 12 | rs << 8 | rm;

    CU_ASSERT_THROWS_ERROR(handle_long_multiply(instruction, &cpu))
}
void test_basic_long_multiply_instruction_set_bits() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction
    uint8_t cond = 0xE;

    // set registers and flags
    flag_t U = 0;
    flag_t A = 0;
    flag_t S = 0;
    reg_t rd_hi = 3;
    reg_t rd_lo = 2;
    reg_t rs = 0;
    reg_t rm = 1;
    instruction_t instruction = cond << 28 | 1 << 23 | U << 22 | A << 21 |
                                S << 20 | rd_hi << 16 | rd_lo << 12 | rs << 8 |
                                0b1001 << 4 | rm;
    // set register values
    uint32_t rm_value = 10;
    uint32_t rs_value = 20;

    // write to registers
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_long_multiply(instruction, &cpu);

    uint32_t actual_hi;
    uint32_t actual_lo;
    read_register(rd_hi, &cpu.registers, &actual_hi);
    read_register(rd_lo, &cpu.registers, &actual_lo);

    CU_ASSERT_EQUAL(actual_lo, rs_value * rm_value)
    CU_ASSERT_EQUAL(actual_hi, 0)
}

int add_multiply_long_tests() {
    CU_pSuite suite = CU_add_suite("Long Multiply Tests", 0, 0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_correct_long_multiply_instruction_set_bits)
    ADD_TEST(test_basic_long_multiply_instruction_set_bits)
    // Register specified shift amount tests
    return CUE_SUCCESS;
}