#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "cpu.h"

void test_EQ_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0x0, state));
    pState->Z = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x0, state));
}

void test_NE_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0x1, state));
    pState->Z = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x1, state));
}
void test_CS_HS_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0x2, state));
    pState->C = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x2, state));
}
void test_CC_LO_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0x3, state));
    pState->C = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x3, state));
}

void test_MI_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0x4, state));
    pState->N = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x4, state));
}
void test_PL_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0x5, state));
    pState->N = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x5, state));
}
void test_VS_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0x6, state));
    pState->V = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x6, state));
}
void test_VC_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0x7, state));
    pState->V = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x7, state));
}

void test_HI_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0x8, state));
    pState->C = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x8, state));
    pState->Z = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x8, state));
    pState->C = 0;
    CU_ASSERT_FALSE(evaluate_cond(0x8, state));
    
}
void test_LS_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0x9, state));
    pState->C = 1;
    CU_ASSERT_FALSE(evaluate_cond(0x9, state));
    pState->Z = 1;
    CU_ASSERT_TRUE(evaluate_cond(0x9, state));
    pState->C = 0;
    CU_ASSERT_TRUE(evaluate_cond(0x9, state));
    
}

void test_GE_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0xA, state));
    pState->V = 1;
    CU_ASSERT_FALSE(evaluate_cond(0xA, state));
    pState->N = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xA, state));
}
void test_LT_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0xB, state));
    pState->V = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xB, state));
    pState->N = 1;
    CU_ASSERT_FALSE(evaluate_cond(0xB, state));
}

void test_GT_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_TRUE(evaluate_cond(0xC, state));
    pState->N = 1;
    CU_ASSERT_FALSE(evaluate_cond(0xC, state));
    pState->V = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xC, state));
    pState->Z = 1;
    CU_ASSERT_FALSE(evaluate_cond(0xC, state));
    pState->N = 0;
    CU_ASSERT_FALSE(evaluate_cond(0xC, state));
    pState->V = 0;
    CU_ASSERT_FALSE(evaluate_cond(0xC, state));
    
}
void test_LE_OPCODE(){
    uint32_t state = 0;
    CPSR * pState = (CPSR *)&state;
    CU_ASSERT_FALSE(evaluate_cond(0xD, state));
    pState->N = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xD, state));
    pState->V = 1;
    CU_ASSERT_FALSE(evaluate_cond(0xD, state));
    pState->Z = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xD, state));
    pState->N = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xD, state));
    pState->V = 1;
    CU_ASSERT_TRUE(evaluate_cond(0xD, state))
    
}
//STARTUP FUNCTIONS


int add_cond_tests(){
    CU_pSuite suite = CU_add_suite("Instruction Cond Tests",0,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test Equal OPCODE: 0x0", test_EQ_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Not Equal OPCODE: 0x1", test_NE_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Carry set/ unsigned higher or same OPCODE: 0x2", test_CS_HS_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test Carry clear / unsigned lower OPCODE: 0x3", test_CS_HS_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Minus / negative  OPCODE: 0x4", test_MI_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Plus / positive or zero OPCODE: 0x5", test_PL_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Overflow OPCODE: 0x6", test_VS_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test No overflow OPCODE: 0x7", test_VC_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test Unsigned higher : 0x8", test_HI_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Unsigned lower or same OPCODE: 0x9", test_LS_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test Signed greater than or equal  OPCODE: 0xA", test_GE_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Signed less than  OPCODE: 0xB", test_LT_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test Signed greater than  OPCODE: 0xC", test_GT_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test Signed less than or equal OPCODE: 0xD", test_LE_OPCODE)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // if (NULL == CU_add_test(suite, "test Always (unconditional)  OPCODE: 0xE", test_VS_OPCODE)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }

    // if (NULL == CU_add_test(suite, "test No overflow OPCODE: 0xE", test_VC_OPCODE)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }

    return CUE_SUCCESS;
}