#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "impl_core.h"
#include "barrel_shifter.h"

// REGISTER ALU

// TEST ALU OPS

void test_no_shift_lsl(){
    BS_FLAGS flags;
    uint32_t value = 0x80000000;
    uint32_t result;
    BS_LSL(value, 0, &flags, &result);
    CU_ASSERT_EQUAL(result, value)
    CU_ASSERT_EQUAL(flags.C, 0)


}

void test_shift1_no_c_lsl(){
    BS_FLAGS flags;
    uint32_t value = 0x40000000;
    uint32_t result;
    BS_LSL(value, 1, &flags, &result);
    CU_ASSERT_EQUAL(result, 0x080000000)
    CU_ASSERT_FALSE(flags.C)
}

void test_shift1_with_c_lsl(){
    BS_FLAGS flags;
    uint32_t value = 0x80000000;
    uint32_t result;
    BS_LSL(value, 1, &flags, &result);
    CU_ASSERT_EQUAL(result, 0)
    CU_ASSERT_TRUE(flags.C)
}

void test_shift1_input_overflow_lsl(){
    BS_FLAGS flags;
    uint32_t value = 0x11;
    uint32_t result;
    BS_LSL(value, 32, &flags, &result);
    printf("%x", result);
    CU_ASSERT_EQUAL(result, 0)
    CU_ASSERT_FALSE(flags.C)
}

void test_no_shift_lsr(){
    BS_FLAGS flags;
    uint32_t value = 0x8;
    uint32_t result;
    BS_LSR(value, 0, &flags, &result);
    CU_ASSERT_EQUAL(result, value)
    CU_ASSERT_EQUAL(flags.C, 0)


}

void test_shift1_no_c_lsr(){
    BS_FLAGS flags;
    uint32_t value = 0x8;
    uint32_t result;
    BS_LSR(value, 1, &flags, &result);
    CU_ASSERT_EQUAL(result, 0x4)
    CU_ASSERT_FALSE(flags.C)
}

void test_shift1_with_c_lsr(){
    BS_FLAGS flags;
    uint32_t value = 0x7;
    uint32_t result;
    BS_LSR(value, 1, &flags, &result);
    CU_ASSERT_EQUAL(result, 0x3)
    CU_ASSERT_TRUE(flags.C)
}

void test_shift1_input_overflow_lsr(){
    BS_FLAGS flags;
    uint32_t value = 0xFFFFFFFF;
    uint32_t result;
    BS_LSR(value, 32, &flags, &result);
    printf("%x", result);
    CU_ASSERT_EQUAL(result, 0)
    CU_ASSERT_FALSE(flags.C)
}

void test_shift_overflow_negative_asr(){
    BS_FLAGS flags;
    uint32_t value = 0x80000000;
    uint32_t result;
    BS_ASR(value, 32, &flags, &result);
    CU_ASSERT_EQUAL(result, 0xFFFFFFFF);
    CU_ASSERT_EQUAL(flags.C, 1)
}

void test_shift_overflow_positive_asr(){
    BS_FLAGS flags;
    uint32_t value = 0x70000000;
    uint32_t result;
    BS_ASR(value, 32, &flags, &result);
    CU_ASSERT_EQUAL(result, 0x0)
    CU_ASSERT_EQUAL(flags.C, 0)
}

void test_shift_negaitive_msb_asr(){
    BS_FLAGS flags;
    uint32_t value = 0x80000000;
    uint32_t result;
    BS_ASR(value, 3, &flags, &result);
    CU_ASSERT_EQUAL(result, 0xF0000000)
    CU_ASSERT_EQUAL(flags.C, 0)
}

void test_shift_positive_msb_asr(){
    BS_FLAGS flags;
    uint32_t value = 0x70000000;
    uint32_t result;
    BS_ASR(value, 4, &flags, &result);
    CU_ASSERT_EQUAL(result, 0x7000000)
    CU_ASSERT_FALSE(flags.C)
}

void test_no_shift_positive_ror(){
    BS_FLAGS flags;
    uint32_t value = 0x70000000;
    uint32_t result;
    BS_ROR(value, 0, &flags, &result);
    CU_ASSERT_EQUAL(result, value)
    CU_ASSERT_FALSE(flags.C)

}

void test_no_shift_negative_ror(){
    BS_FLAGS flags;
    uint32_t value = 0xF0000000;
    uint32_t result;
    BS_ROR(value, 0, &flags, &result);
    CU_ASSERT_EQUAL(result, value)
    CU_ASSERT_TRUE(flags.C)
}

void test_32_shift_ror(){
    BS_FLAGS flags;
    uint32_t value = 0xF0000000;
    uint32_t result;
    BS_ROR(value, 32, &flags, &result);
    CU_ASSERT_EQUAL(result, value)
    CU_ASSERT_TRUE(flags.C)
}

void test_normal_shift_ror(){
    BS_FLAGS flags;
    uint32_t value = 0xF000000E;
    uint32_t result;
    BS_ROR(value, 4, &flags, &result);
    CU_ASSERT_EQUAL(result, 0xEF000000)
    CU_ASSERT_TRUE(flags.C)
}

void test_shift_over_32_ror(){
    BS_FLAGS flags;
    uint32_t value = 0xF000000E;
    uint32_t result;
    BS_ROR(value, 36, &flags, &result);
    CU_ASSERT_EQUAL(result, 0xEF000000)
    CU_ASSERT_TRUE(flags.C)
}

int add_barrel_shifter_tests(){
    CU_pSuite suite = CU_add_suite("Barrel Shifter Tests",0,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test no shift lsl", test_no_shift_lsl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_no_c_lsl", test_shift1_no_c_lsl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_with_c_lsl", test_shift1_with_c_lsl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_input_overflow_lsl", test_shift1_input_overflow_lsl)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_no_shift_lsr", test_no_shift_lsr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_input_overflow_lsr", test_shift1_input_overflow_lsr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_no_c_lsr", test_shift1_no_c_lsr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift1_with_c_lsr", test_shift1_with_c_lsr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift_overflow_negative_asr", test_shift_overflow_negative_asr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift_overflow_positive_asr", test_shift_overflow_positive_asr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift_positive_msb_asr", test_shift_positive_msb_asr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift_negaitive_msb_asr", test_shift_negaitive_msb_asr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_32_shift_ror", test_32_shift_ror)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_normal_shift_ror", test_normal_shift_ror)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_no_shift_negative_ror", test_no_shift_negative_ror)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_no_shift_positive_ror", test_no_shift_positive_ror)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_shift_over_32_ror", test_shift_over_32_ror)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}
