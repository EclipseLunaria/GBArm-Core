#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "memory_bus.h"
#include "data_transfer.h"
#include "registers.h"
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
    CU_ASSERT_EQUAL(new_rn_value, 1)
}

void test_store_byte_immediate_offset_up_writeback() {
    CPU cpu;
    init_cpu(&cpu);

    flag_t I = 1;  // 0: register op, 1: immediate op
    flag_t P = 0;  // 0: post-index 1: pre-index
    flag_t U = 1;  // 1: up, 0: down
    flag_t B = 1;  // 0: word, 1: byte
    flag_t W = 1;  // writeback
    flag_t L = 0;  // 0: store, 1: load
    reg_t rn = 1;  // base register
    reg_t rd = 0;
    uint16_t offset = 0x69;
    instruction_t instruction =
        0xE << 28 | 1 << 26 | I << 25 | P << 24 | U << 23 | B << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 | offset;

    write_register(rn, 0, &cpu.registers);
    write_register(rd, 0xEE, &cpu.registers);

    int status = SDT(instruction, &cpu);

    CU_ASSERT_EQUAL(status, 0)

    byte_t actual;
    uint32_t new_rn_val;
    memory_read_byte(0x0, &cpu.memory, &actual);
    read_register(rn, &cpu.registers, &new_rn_val);
    CU_ASSERT_EQUAL(actual, 0xEE)
    CU_ASSERT_EQUAL(new_rn_val, 0x69)
}

// SPECIAL DATA TRANSFER TESTS

// USING IMMEDIATE VALUES
// L = 0
void test_store_halfword() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 0;
    flag_t L = 0;
    reg_t rn = 1;
    reg_t rd = 0;
    uint8_t offset = 0xFF;
    uint8_t opcode = 0b01;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    uint32_t rd_value = 0x1FF;
    uint32_t rn_value = 0;

    write_register(rd, rd_value, &cpu.registers);
    write_register(rn, rn_value, &cpu.registers);

    STDT(instruction, &cpu);

    halfword_t actual;
    memory_read_halfword(offset, &cpu.memory, &actual);
    CU_ASSERT_EQUAL(actual, 0x1FF);
}
void test_load_double_word() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 0;
    flag_t L = 0;
    reg_t rn = 1;
    reg_t rd = 5;
    uint8_t offset = 0xF0;
    uint8_t opcode = 0b10;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    // setup initial values
    memory_write_word(0xF0, 420710, &cpu.memory);
    memory_write_word(0xF4, 420711, &cpu.memory);

    STDT(instruction, &cpu);
    word_t actual_hi, actual_lo;
    read_register(rd, &cpu.registers, &actual_hi);
    read_register(rd + 1, &cpu.registers, &actual_lo);

    CU_ASSERT_EQUAL(actual_hi, 420710)
    CU_ASSERT_EQUAL(actual_lo, 420711)
}
void test_store_double_word() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 1;
    flag_t L = 0;
    reg_t rn = 1;
    reg_t rd = 5;
    uint8_t offset = 0xF0;
    uint8_t opcode = 0b11;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    write_register(rd, 420710, &cpu.registers);
    write_register(rd + 1, 420711, &cpu.registers);
    // setup initial values

    STDT(instruction, &cpu);
    word_t actual_hi, actual_lo;
    memory_read_word(0xF0, &cpu.memory, &actual_hi);
    memory_read_word(0xF4, &cpu.memory, &actual_lo);

    CU_ASSERT_EQUAL(actual_hi, 420710)
    CU_ASSERT_EQUAL(actual_lo, 420711)
}

// L = 1
void test_load_usigned_halfword() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 0;
    flag_t L = 1;
    reg_t rn = 1;
    reg_t rd = 0;
    uint8_t offset = 0xF0;
    uint8_t opcode = 0b01;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    uint32_t rn_value = 0xF;
    write_register(rn, rn_value, &cpu.registers);
    memory_write_halfword(offset + rn_value, 0xFFF, &cpu.memory);

    STDT(instruction, &cpu);

    word_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, 0xFFF);
}
void test_load_signed_byte() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 0;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 0;
    flag_t L = 1;
    reg_t rn = 1;
    reg_t rd = 0;
    uint8_t offset = 0x0;
    uint8_t opcode = 0b10;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    uint8_t rn_value = 0x0;
    uint8_t mem_value = (uint8_t)-100;
    write_register(rn, rn_value, &cpu.registers);
    memory_write_byte(rn_value, mem_value, &cpu.memory);

    STDT(instruction, &cpu);

    word_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, -100)
}
void test_load_signed_halfword() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 0;
    flag_t U = 1;
    flag_t I = 1;
    flag_t W = 0;
    flag_t L = 1;
    reg_t rn = 1;
    reg_t rd = 0;
    uint8_t offset = 0x0;
    uint8_t opcode = 0b11;

    instruction_t instruction = cond << 28 | P << 24 | U << 23 | I << 22 | W << 21 | L << 20 | rn << 16 | rd << 12 |
                                ((offset >> 4) & 0xF) << 8 | opcode << 5 | (offset & 0xF);

    uint8_t rn_value = 0x0;
    halfword_t mem_value = -1;
    write_register(rn, rn_value, &cpu.registers);
    memory_write_halfword(rn_value, mem_value, &cpu.memory);

    STDT(instruction, &cpu);

    word_t actual;
    read_register(rd, &cpu.registers, &actual);
    CU_ASSERT_EQUAL(actual, -1)
}

void test_load_block_data() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 0;
    flag_t U = 1;
    flag_t S = 0;
    flag_t W = 0;
    flag_t L = 1;
    reg_t rn = 5;
    uint32_t rn_value = 0xF;
    uint16_t reg_list = 0x03;
    instruction_t instruction =
        cond << 28 | 1 << 27 | P << 24 | U << 23 | S << 22 | W << 21 | L << 20 | rn << 16 | reg_list;

    // set initial state
    write_register(rn, rn_value, &cpu.registers);
    memory_write_word(0xF, 100, &cpu.memory);
    memory_write_word(0x13, 200, &cpu.memory);

    ASSERT_REGISTER_EQUALS(rn, 0xF, &cpu.registers);

    BDT(instruction, &cpu);
    ASSERT_REGISTER_EQUALS(0, 100, &cpu.registers);
    ASSERT_REGISTER_EQUALS(1, 200, &cpu.registers);
}

void test_store_block_data_with_writeback() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 0;
    flag_t U = 1;
    flag_t S = 0;
    flag_t W = 1;
    flag_t L = 0;
    reg_t rn = 5;
    uint32_t rn_value = 0xF;
    uint16_t reg_list = 0x07;
    instruction_t instruction =
        cond << 28 | 1 << 27 | P << 24 | U << 23 | S << 22 | W << 21 | L << 20 | rn << 16 | reg_list;

    // set initial state
    write_register(rn, rn_value, &cpu.registers);
    write_register(0, 100, &cpu.registers);
    write_register(1, 200, &cpu.registers);
    write_register(2, 300, &cpu.registers);

    BDT(instruction, &cpu);

    uint32_t post_rn_value;
    read_register(rn, &cpu.registers, &post_rn_value);
    ASSERT_REGISTER_EQUALS(rn, rn_value + 3 * 4, &cpu.registers);
    uint32_t m1, m2, m3;
    memory_read_word(rn_value, &cpu.memory, &m1);
    memory_read_word(rn_value + 4, &cpu.memory, &m2);
    memory_read_word(rn_value + 8, &cpu.memory, &m3);

    CU_ASSERT_EQUAL(m1, 100)
    CU_ASSERT_EQUAL(m2, 200)
    CU_ASSERT_EQUAL(m3, 300)
}
void test_store_block_data_with_writeback_preincrementing() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 1;
    flag_t S = 0;
    flag_t W = 1;
    flag_t L = 0;
    reg_t rn = 0;
    uint32_t rn_value = 0x1000;
    uint16_t reg_list = 1 << 1 | 1 << 5 | 1 << 7;
    instruction_t instruction =
        cond << 28 | 1 << 27 | P << 24 | U << 23 | S << 22 | W << 21 | L << 20 | rn << 16 | reg_list;

    // set initial state
    write_register(rn, rn_value, &cpu.registers);
    write_register(1, 100, &cpu.registers);
    write_register(5, 200, &cpu.registers);
    write_register(7, 300, &cpu.registers);

    BDT(instruction, &cpu);

    uint32_t post_rn_value;
    read_register(rn, &cpu.registers, &post_rn_value);
    CU_ASSERT_EQUAL(post_rn_value, 0x100C)
}
void test_store_block_data_with_writeback_post_decrementing() {
    CPU cpu;
    init_cpu(&cpu);

    uint8_t cond = 0xE;
    flag_t P = 1;
    flag_t U = 0;
    flag_t S = 0;
    flag_t W = 1;
    flag_t L = 0;
    reg_t rn = 0;
    uint32_t rn_value = 0x1000;
    uint16_t reg_list = 1 << 1 | 1 << 5 | 1 << 7;
    instruction_t instruction =
        cond << 28 | 1 << 27 | P << 24 | U << 23 | S << 22 | W << 21 | L << 20 | rn << 16 | reg_list;

    // set initial state
    write_register(rn, rn_value, &cpu.registers);
    write_register(1, 100, &cpu.registers);
    write_register(5, 200, &cpu.registers);
    write_register(7, 300, &cpu.registers);

    BDT(instruction, &cpu);

    uint32_t post_rn_value;
    read_register(rn, &cpu.registers, &post_rn_value);
    CU_ASSERT_EQUAL(post_rn_value, 0x0FF4)
}

int add_data_transfer_tests() {
    CU_pSuite suite = CU_add_suite("Data Transfer Tests", 0, 0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_store_register_writeback_byte_data_up)
    ADD_TEST(test_store_byte_immediate_offset_up_writeback)

    // Special data transfers
    ADD_TEST(test_store_halfword)
    ADD_TEST(test_load_double_word)
    ADD_TEST(test_store_double_word)

    ADD_TEST(test_load_usigned_halfword)
    ADD_TEST(test_load_signed_byte)
    ADD_TEST(test_load_signed_halfword)

    ADD_TEST(test_load_block_data)
    ADD_TEST(test_store_block_data_with_writeback)
    ADD_TEST(test_store_block_data_with_writeback_preincrementing)
    ADD_TEST(test_store_block_data_with_writeback_post_decrementing)
    return CUE_SUCCESS;
}
