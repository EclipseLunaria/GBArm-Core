#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_macros.h"
#include "core.h"
#include "assembler.h"
#include "test_helpers.h"

void test_simple_tokenize_instruction(){
    char buf[] = "MOV R0, R1";
    char tokens[16][8];

    tokenize_instruction(buf, tokens);
    printf("TOKEN 0: %s\n", tokens[0]);

    for (int i = 0; i < 16 && strlen(tokens[i]) > 0; i++) {
        printf("buf: %s\n", tokens[i]);
    }
    // CU_ASSERT_STRING_EQUAL(tokens[0], "MOV")
    // CU_ASSERT_STRING_EQUAL(tokens[1], "R0")
    // CU_ASSERT_STRING_EQUAL(tokens[2], "R1")
}

void test_immediate_alu_mov(){
    char buf[512];
    strcpy(buf, "MOV R0, #0;");
    uint32_t actual;
    uint32_t expected = 0xE3A00000;
    encode_instruction(buf, &actual);
    PRINTX(expected);
}

void test_EOR_opcode(){
    char buf[512];
    char tokens[16][8];
    strcpy(buf, "EOR R0, R1;");
    int n = tokenize_instruction(buf, tokens);
    uint32_t actual;
    encode_alu_instruction(tokens, n, &actual);
    CU_ASSERT_EQUAL((actual >> 21) & 0xF, 1)
}

void test_set_cond() {
    char buf[512] = "MOVNE R0, R1";
    char tokens[16][8];
    int n = tokenize_instruction(buf, tokens);
    uint32_t actual;
    encode_alu_instruction(tokens, n, &actual);

    CU_ASSERT_EQUAL(actual, 0x1 << 28)

}
void test_dest_register_parse() {
    char buf[512] = "MOVNE R0, R1";
    char tokens[16][8];
    int n = tokenize_instruction(buf, tokens);
    uint32_t actual;
    encode_alu_instruction(tokens, n, &actual);

    CU_ASSERT_EQUAL(actual, 0x1 << 28)

}

int mk_throws_invalid_opcode(char * s){
    CHECK_ERROR(find_alu_opcode(s),"Invalid ALU Opcode: %s", s)
    return 0;
}

int mk_double_throw(char * s){
    CHECK_ERROR(mk_throws_invalid_opcode(s), "Invalid ALU Opcode double: %s",s)
    return 0;
}
void test_find_invalid_alu_opcode(){

    CU_ASSERT_EQUAL(mk_throws_invalid_opcode("MAV"), -3)
}
void test_find_invalid_alu_opcode_double(){

    CU_ASSERT_EQUAL(mk_double_throw("MAV"), -4)
}

void test_encode_immediate_decimal_low(){
    char instruction[64] = "ADDS R1, R3, #100";
    uint32_t encoded;
    encode_instruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 100)
}

void test_encode_immediate_hex_low(){
    char instruction[64] = "ADDS R1, R3, #0x44";
    uint32_t encoded;
    encode_instruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x44)
}

void test_encode_add_operation_register_shift(){
    char instruction[64] = "ADDS R1, R3, R4, LSL r5";
    uint32_t encoded;
    encode_instruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x514)

}

void test_encode_add_operation_register_immediate_shift(){
    char instruction[64] = "ADDS R1, R3, R4, LSL #0x2";
    uint32_t encoded;
    encode_instruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x104)

}

void test_ADD_two_registers_into_third_register(){
    uint32_t r0v, r1v;
    CPU cpu;
    init_cpu(&cpu);

    char * instructions[] = {
        "MOV r0 #10",
        "MOV r1 #10"
    };
    int r = execute_alu_instructions(instructions, 2, &cpu);
    read_register(0, &cpu.registers, &r0v);
    read_register(1, &cpu.registers, &r1v);
    CU_ASSERT_EQUAL(r0v, 10)
    CU_ASSERT_EQUAL(r1v, 10)
    CU_ASSERT_EQUAL(r, 2);

    char i[64] = "ADD r2 r0 r1";
    uint32_t actual;
    uint32_t expected =  0xE0802001;

    encode_instruction(i, &actual);
    CU_ASSERT_EQUAL(actual, expected)
    alu_execute(actual,&cpu);

    uint32_t r2v;
    read_register(2, &cpu.registers, &r2v);
    CU_ASSERT_EQUAL(r2v, 20)

}

void test_ADD_two_registers_given_two_registers(){
    uint32_t r0v;
    uint32_t r1v;
    CPU cpu;
    init_cpu(&cpu);

    char * instructions[] = {
        "MOV r1 #10",
        "ADD r0 r1",
    };
    int r = execute_alu_instructions(instructions, 2, &cpu);
    read_register(1, &cpu.registers, &r1v);
    CU_ASSERT_EQUAL(r1v, 10)
    CU_ASSERT_EQUAL(r, 2);
    read_register(0, &cpu.registers, &r0v);
    CU_ASSERT_EQUAL(r0v, 10)

}

void test_encode_alu_missing_reg_shift_operand(){
    char instruction[64] = "ADDS R1, R3, r4, LSL";
    uint32_t encoded;
    CU_ASSERT_TRUE(encode_instruction(instruction, &encoded) < 0)
}
void test_encode_alu_invalid_reg_imm_shift(){
    char instruction[64] = "ADDS R1, R3, r4, LSL #200";
    uint32_t encoded;
    CU_ASSERT_TRUE(encode_instruction(instruction, &encoded) < 0)
}

void test_encode_alu_invalid_shift_op(){
    char instruction[64] = "ADDS R1, R3, r4, LSA r5";
    uint32_t encoded;
    CU_ASSERT_TRUE(encode_instruction(instruction, &encoded) < 0)

}
void test_encode_alu_invalid_invalid_parameter_value(){
    char instruction[64] = "ADDS R1, R3, r4, LSL d5";
    uint32_t encoded;
    CU_ASSERT_TRUE(encode_instruction(instruction, &encoded) < 0)

}

void test_encode_alu_invalid_shift_rm_as_op(){
    char instruction[64] = "ADDS R1, R3, r4, LSA r55";
    uint32_t encoded;
    CU_ASSERT_TRUE(encode_instruction(instruction, &encoded)<0)

}

void test_mov_with_encode_two_register(){
    char instruction[64] = "MOV r1 r2";
    uint32_t encoded;
    CU_ASSERT_FALSE(encode_instruction(instruction, &encoded))
    CU_ASSERT_EQUAL((encoded >> 16) & 0xF, 1)
    CU_ASSERT_EQUAL((encoded >> 12) & 0xF, 1)
    CU_ASSERT_EQUAL(encoded & 0xF, 2)

}
void test_mov_with_two_values_one_immediate(){
    char instruction[64] = "MOV r1 #10";
    uint32_t encoded;
    CU_ASSERT_FALSE(encode_instruction(instruction, &encoded))
    CU_ASSERT_EQUAL((encoded >> 16) & 0xF, 1)
    CU_ASSERT_EQUAL((encoded >> 12) & 0xF, 1)
    CU_ASSERT_EQUAL(encoded & 0xF, 10)

}


int add_assembler_tests(){
    CU_pSuite suite = CU_add_suite("Assembler Tests",0,0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_simple_tokenize_instruction);
    ADD_TEST(test_immediate_alu_mov);
    ADD_TEST(test_EOR_opcode);
    ADD_TEST(test_encode_immediate_decimal_low)
    ADD_TEST(test_encode_immediate_hex_low)
    ADD_TEST(test_encode_alu_missing_reg_shift_operand)
    ADD_TEST(test_encode_alu_invalid_shift_op)
    ADD_TEST(test_encode_alu_invalid_shift_rm_as_op)
    ADD_TEST(test_encode_add_operation_register_shift)
    ADD_TEST(test_encode_alu_invalid_reg_imm_shift)
    ADD_TEST(test_encode_add_operation_register_immediate_shift)
    ADD_TEST(test_encode_alu_invalid_invalid_parameter_value)
    ADD_TEST(test_mov_with_encode_two_register)
    ADD_TEST(test_mov_with_two_values_one_immediate)
    ADD_TEST(test_find_invalid_alu_opcode)
    ADD_TEST(test_find_invalid_alu_opcode_double)
    ADD_TEST(test_ADD_two_registers_into_third_register)
    ADD_TEST(test_ADD_two_registers_given_two_registers)

    // Register specified shift amount tests
    return CUE_SUCCESS;
}
