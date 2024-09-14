#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "cpu.h"



void test_cpu_init(){
    CPU cpu;
    init_cpu(&cpu);
    // check system memory.
    CU_ASSERT_PTR_NOT_NULL(cpu.registers.current_registers)
    CU_ASSERT_PTR_EQUAL(cpu.registers.current_registers->p_registers[0], &cpu.registers.register_data.registers[0])
    CU_ASSERT_EQUAL(cpu.clock_cycles, 0)
    CU_ASSERT_EQUAL(cpu.loaded_instruction, 0)
    CU_ASSERT_EQUAL(cpu.sleep_cycles, 0)
}


void test_clock_cpu_iteration(){
    CPU cpu;
    init_cpu(&cpu);
    CU_ASSERT_EQUAL(cpu.clock_cycles, 0);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0);
    clock_cpu(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 4);
}   


void test_clock_cpu_load_instruction(){
    CPU cpu;
    init_cpu(&cpu);
    word_t testVal = 5555;
    write_word(0,&testVal);
    CU_ASSERT_EQUAL(cpu.loaded_instruction, 0);
    clock_cpu(&cpu);
    CU_ASSERT_EQUAL(cpu.loaded_instruction, testVal)
    CU_ASSERT_EQUAL(*cpu.registers.PC, 4);
}   

int add_cpu_tests(){
    CU_pSuite suite = CU_add_suite("CPU Tests",0,0);

    if (suite == NULL) return CU_get_error();


    if (NULL == CU_add_test(suite, "test init cpu", test_cpu_init)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test clock cpu iteration", test_clock_cpu_iteration)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test clock cpu load instruction", test_clock_cpu_load_instruction)) {
        CU_cleanup_registry();
        return CU_get_error();
    }






    return CUE_SUCCESS;
}