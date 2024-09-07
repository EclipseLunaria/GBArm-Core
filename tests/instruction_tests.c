#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "instruction.h"




int add_instruction_tests(){
    CU_pSuite suite = CU_add_suite("Instruction Tests",0,0);

    if (suite == NULL) return CU_get_error();

    // if (NULL == CU_add_test(suite, "test init cpu", test_cpu_init)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }
    

    return CUE_SUCCESS;
}