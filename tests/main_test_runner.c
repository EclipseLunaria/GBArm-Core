#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
extern int add_bus_tests();


int main() {
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    add_bus_tests();


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();

}