#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_macros.h"
#include "core.h"
#include "alu.h"

// REGISTER ALU

// TEST ALU OPS

// AND TESTS

void test_AND_no_shift(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x10;
    uint32_t expected = 0x10;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_AND_negative(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x80000000;
    uint32_t op2 = 0xF0000000;
    uint32_t expected = 0x80000000;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_TRUE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_AND_start_non_zero_to_zero(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x0;
    uint32_t op2 = 0xFFFFF;
    uint32_t expected = 0x0;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_AND_pass_c_flag(){
    BS_FLAGS flags;
    flags.C = 1;

    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x0F;
    uint32_t expected = 0x0;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}

void test_EOR_no_shift(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF;
    uint32_t op2 = 0x1;
    uint32_t expected = 0x1;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_EOR_negative(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x80000000;
    uint32_t op2 = 0xE0000000;
    uint32_t expected = 0xF0000000;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_TRUE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_EOR_start_non_zero_to_zero(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF;
    uint32_t op2 = 0xF;
    uint32_t expected = 0x0;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}
void test_EOR_pass_c_flag(){
    BS_FLAGS flags;
    flags.C = 1;

    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x0F;
    uint32_t expected = 0xFF;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.IsArithmetic)
}

void test_SUB_basic(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x10;
    uint32_t expected = 0xE0;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Positive result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_negative_result(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x10;
    uint32_t op2 = 0x20;
    uint32_t expected = 0xFFFFFFF0; // -16 in 2's complement
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_TRUE(flags.N)   // Negative result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_zero_result(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x20;
    uint32_t op2 = 0x20;
    uint32_t expected = 0x0;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Not negative
    CU_ASSERT_TRUE(flags.Z)   // Result is zero
}

void test_SUB_signed_overflow(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x7FFFFFFF;  // -2147483648 in signed 32-bit
    uint32_t op2 = 0xFFFFFFFF;  // -1
    uint32_t expected = 0x80000000;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.V)   // Signed overflow
    CU_ASSERT_TRUE(flags.N)   // Negative result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_no_overflow(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x7FFFFFFF;  // 2147483647 in signed 32-bit
    uint32_t op2 = 0x00000001;  // 1
    uint32_t expected = 0x7FFFFFFE;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Positive result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

// void test_op_template(){
//     BS_FLAGS flags;
//     uint32_t result;
//     uint32_t op1 = 0xF0;
//     uint32_t op2 = 0x10;
//     uint32_t expected = 0x10;
//     ALU_AND(op1, op2, &flags, &result);
//     // assert result
//     CU_ASSERT_EQUAL(result, expected)
//     // assert flags
//     CU_ASSERT_TRUE(flags.C)
//     CU_ASSERT_FALSE(flags.C)
//     CU_ASSERT_TRUE(flags.N)
//     CU_ASSERT_FALSE(flags.N)
//     CU_ASSERT_TRUE(flags.V)
//     CU_ASSERT_FALSE(flags.V)
//     CU_ASSERT_TRUE(flags.Z)
//     CU_ASSERT_FALSE(flags.Z)
//     CU_ASSERT_TRUE(flags.IsArithmetic)
//     CU_ASSERT_FALSE(flags.IsArithmetic)
// }


int add_alu_tests(){
    CU_pSuite suite = CU_add_suite("ALU Tests",0,0);

    if (suite == NULL) return CU_get_error();

    ADD_TEST(test_AND_negative )
    ADD_TEST(test_AND_no_shift )
    ADD_TEST(test_AND_pass_c_flag )
    ADD_TEST(test_AND_start_non_zero_to_zero)
    ADD_TEST(test_EOR_no_shift)
    ADD_TEST(test_EOR_start_non_zero_to_zero)
    ADD_TEST(test_EOR_pass_c_flag )

    // sub 
    ADD_TEST(test_SUB_basic);
    ADD_TEST(test_SUB_negative_result);
    ADD_TEST(test_SUB_zero_result);
    ADD_TEST(test_SUB_signed_overflow);
    ADD_TEST(test_SUB_no_overflow);
    return CUE_SUCCESS;
}