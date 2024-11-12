#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>

extern int add_alu_tests();
extern int add_register_tests();
extern int add_instruction_tests();
extern int add_utils_tests();
extern int add_multiply_tests();
extern int add_multiply_long_tests();
extern int add_memory_bus_tests();
extern int add_data_transfer_tests();
extern int add_psr_tests();
extern int add_branch_tests();


int main(int argc, char ** argv) {
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    int log_mode = CU_BRM_VERBOSE;
    if (argc > 1 && !strcmp(argv[1], "-s")){ 
       log_mode = CU_BRM_SILENT;

    }
    add_alu_tests();
    add_register_tests();
    add_instruction_tests();
    add_utils_tests();
    add_multiply_tests();
    add_multiply_long_tests();
    add_memory_bus_tests();
    add_data_transfer_tests();
	add_psr_tests();
	add_branch_tests();

    CU_pTestRegistry test_registry =CU_get_registry();
    
    CU_basic_set_mode(log_mode);
    CU_basic_run_tests();
}
