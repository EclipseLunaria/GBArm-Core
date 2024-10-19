#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "test_macros.h"
#include "internal/multiply.h"
#include "internal/registers.h"

void test_multiply_correct_instruction_set_bits() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 0;
    flag_t S = 0;
    reg_t rn = 0;
    reg_t rs = 0;
    reg_t rm = 1;
    reg_t rd = 2;
    instruction_t instruction =
        cond << 28 | A << 21 | S << 20 | rd << 16 | rn << 12 | rs << 8 | rm;

    // set register values
    uint32_t rm_value = 10;
    uint32_t rs_value = 20;

    // write to registers
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    CU_ASSERT_THROWS_ERROR(handle_multiply(instruction, &cpu))
}

void test_basic_multiply_no_condition_set() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 0;
    flag_t S = 0;
    reg_t rn = 0;
    reg_t rs = 0;
    reg_t rm = 1;
    reg_t rd = 2;
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rm_value = 10;
    uint32_t rs_value = 20;

    // write to registers
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value)
}

void test_basic_multiply_with_negative_set() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 0;
    flag_t S = 1;
    reg_t rn = 0;
    reg_t rs = 0;
    reg_t rm = 1;
    reg_t rd = 2;
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rm_value = 100;
    uint32_t rs_value = -1;

    // write to registers
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value)
    CU_ASSERT_TRUE(cpu.CPSR->N)
}
void test_basic_multiply_no_condition_codes_rn_ignored() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 0;
    flag_t S = 0;
    reg_t rn = 3;
    reg_t rs = 0;
    reg_t rm = 1;
    reg_t rd = 2;
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rn_value = 100;
    uint32_t rm_value = 10;
    uint32_t rs_value = 20;

    // write to registers
    write_register(rn, rn_value, &cpu.registers);
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value)
}

void test_multiply_accumulate_no_cond_set() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 1;
    flag_t S = 0;
    reg_t rd = 0;
    reg_t rn = 1;
    reg_t rs = 2;
    reg_t rm = 3;
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rm_value = 100;
    uint32_t rs_value = 10;
    uint32_t rn_value = 100;

    // write to registers
    write_register(rn, rn_value, &cpu.registers);
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value + rn_value)
}
void test_multiply_accumulate_with_negative_set() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 1;
    flag_t S = 1;
    reg_t rd = 0;
    reg_t rn = 1;
    reg_t rs = 2;
    reg_t rm = 3;
    // build instruction
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rm_value = 100;
    uint32_t rs_value = 10;
    uint32_t rn_value = -10000;

    // write to registers
    write_register(rn, rn_value, &cpu.registers);
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value + rn_value)
    CU_ASSERT_TRUE(cpu.CPSR->N)
}
void test_multiply_accumulate_to_zero_with_z_set() {
    CPU cpu;
    init_cpu(&cpu);
    // build instruction

    uint8_t cond = 0xE;

    // set registers and flags
    flag_t A = 1;
    flag_t S = 1;
    reg_t rd = 0;
    reg_t rn = 1;
    reg_t rs = 2;
    reg_t rm = 3;
    // build instruction
    instruction_t instruction = cond << 28 | A << 21 | S << 20 | rd << 16 |
                                rn << 12 | rs << 8 | 0b1001 << 4 | rm;

    // set register values
    uint32_t rm_value = 100;
    uint32_t rs_value = 10;
    uint32_t rn_value = -1000;

    // write to registers
    write_register(rn, rn_value, &cpu.registers);
    write_register(rs, rs_value, &cpu.registers);
    write_register(rm, rm_value, &cpu.registers);

    // execute instruction
    handle_multiply(instruction, &cpu);

    uint32_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, rs_value * rm_value + rn_value)
    CU_ASSERT_FALSE(cpu.CPSR->N)
    CU_ASSERT_TRUE(cpu.CPSR->Z)
}

int add_multiply_tests() {
    CU_pSuite suite = CU_add_suite("Multiply Tests", 0, 0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_multiply_correct_instruction_set_bits)
    ADD_TEST(test_basic_multiply_no_condition_set)
    ADD_TEST(test_basic_multiply_with_negative_set)
    ADD_TEST(test_basic_multiply_no_condition_codes_rn_ignored)

    // Accumulate Tests
    ADD_TEST(test_multiply_accumulate_no_cond_set)
    ADD_TEST(test_multiply_accumulate_with_negative_set)
    ADD_TEST(test_multiply_accumulate_to_zero_with_z_set)

    // Register specified shift amount tests
    return CUE_SUCCESS;
}
