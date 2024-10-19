#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>

#include "test_macros.h"

extern int add_alu_tests();
extern int add_register_tests();
extern int add_instruction_tests();
extern int add_utils_tests();
extern int add_multiply_tests();
extern int add_multiply_long_tests();
extern int add_memory_bus_tests();
extern int add_data_transfer_tests();


int main() {
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }
    
    add_alu_tests();

    add_register_tests();
    add_instruction_tests();
    add_utils_tests();
    add_multiply_tests();
    add_multiply_long_tests();
    add_memory_bus_tests();
    add_data_transfer_tests();

    CU_pTestRegistry test_registry =CU_get_registry();
    
    for (int i = 0; i < test_registry->uiNumberOfSuites; ++i){
        CU_pSuite suite = CU_get_suite_by_index(i, test_registry);
        CU_ErrorCode result = CU_run_suite(suite); 
         
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
}
