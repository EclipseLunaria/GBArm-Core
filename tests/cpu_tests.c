#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "cpu.h"

void test_inital_CSRP_status(){
    CU_ASSERT_EQUAL(CSPR_state, 0);
}

void test_set_flag(){
    CSPR_set_flag(A,1);
    CU_ASSERT_TRUE(CSPR_state&A);
    CU_ASSERT_FALSE(CSPR_state&N);
}

void test_set_get_flag(){
    CSPR_set_flag(A,3);
    CU_ASSERT_TRUE(CSPR_get_flag(A));
    CU_ASSERT_FALSE(CSPR_get_flag(N))
}


//STARTUP FUNCTIONS

int startup(void){
    CSPR_state = 0;
    return CUE_SUCCESS;
}

int add_cpu_tests(){
    CU_pSuite suite = CU_add_suite("CPU Tests",startup,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test initial CSRP value", test_inital_CSRP_status)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test set CSRP flag value", test_set_flag)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test set and getting CSRP flag value", test_set_get_flag)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    return CUE_SUCCESS;
}