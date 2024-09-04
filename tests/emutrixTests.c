#include <CUnit.h>
#include <Basic.h>
int main() {
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite pSuite = CU_add_suite("Bus_Suite",0,0);

    if(NULL==pSuite){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add Tests

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();

}