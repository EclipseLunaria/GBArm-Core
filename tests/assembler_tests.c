#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_macros.h"
#include "core.h"
#include "assembler.h"

void test_simple_tokenize_instruction(){
    char buf[] = "MOV R0, R1";
    char tokens[16][8];

    tokenizeInstruction(buf, tokens);
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
    encodeInstruction(buf, &actual);
    PRINTX(expected);
}

void test_EOR_opcode(){
    char buf[512];
    char tokens[16][8];
    strcpy(buf, "EOR R0, R1;");
    int n = tokenizeInstruction(buf, tokens);
    uint32_t actual;
    encodeALUInstruction(tokens, n, &actual);
    CU_ASSERT_EQUAL((actual >> 21) & 0xF, 1)
}

void test_set_cond() {
    char buf[512] = "MOVNE R0, R1";
    char tokens[16][8];
    int n = tokenizeInstruction(buf, tokens);
    uint32_t actual;
    encodeALUInstruction(tokens, n, &actual);

    CU_ASSERT_EQUAL(actual, 0x1 << 28)

}
void test_dest_register_parse() {
    char buf[512] = "MOVNE R0, R1";
    char tokens[16][8];
    int n = tokenizeInstruction(buf, tokens);
    uint32_t actual;
    encodeALUInstruction(tokens, n, &actual);

    CU_ASSERT_EQUAL(actual, 0x1 << 28)

}

void test_encode_immediate_decimal_low(){
    char instruction[64] = "ADDS R1, R3, #100";
    uint32_t encoded;
    encodeInstruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 100)
}

void test_encode_immediate_hex_low(){
    char instruction[64] = "ADDS R1, R3, #0x44";
    uint32_t encoded;
    encodeInstruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x44)
}

void test_encode_add_operation_register_shift(){
    char instruction[64] = "ADDS R1, R3, R4, LSL r5";
    uint32_t encoded;
    encodeInstruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x514)

}

void test_encode_add_operation_register_immediate_shift(){
    char instruction[64] = "ADDS R1, R3, R4, LSL #0x2";
    uint32_t encoded;
    encodeInstruction(instruction, &encoded);
    CU_ASSERT_EQUAL(encoded & 0xFFF, 0x104)

}


void test_encode_alu_missing_reg_shift_operand(){
    char instruction[64] = "ADDS R1, R3, r4, LSL";
    uint32_t encoded;
    CU_ASSERT_EQUAL(encodeInstruction(instruction, &encoded), -1)
}
void test_encode_alu_invalid_reg_imm_shift(){
    char instruction[64] = "ADDS R1, R3, r4, LSL #200";
    uint32_t encoded;
    CU_ASSERT_EQUAL(encodeInstruction(instruction, &encoded), -1)
}

void test_encode_alu_invalid_shift_op(){
    char instruction[64] = "ADDS R1, R3, r4, LSA r5";
    uint32_t encoded;
    CU_ASSERT_EQUAL(encodeInstruction(instruction, &encoded), -1)

}
void test_encode_alu_invalid_invalid_parameter_value(){
    char instruction[64] = "ADDS R1, R3, r4, LSL d5";
    uint32_t encoded;
    CU_ASSERT_EQUAL(encodeInstruction(instruction, &encoded), -1)

}

void test_encode_alu_invalid_shift_rm_as_op(){
    char instruction[64] = "ADDS R1, R3, r4, LSA r55";
    uint32_t encoded;
    CU_ASSERT_EQUAL(encodeInstruction(instruction, &encoded), -1)

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

    // Register specified shift amount tests 
    return CUE_SUCCESS;
}