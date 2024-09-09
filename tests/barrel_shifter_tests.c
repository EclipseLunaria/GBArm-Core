#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "core.h"
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
    CU_ASSERT_FALSE(flags.Z)
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

    return CUE_SUCCESS;
}