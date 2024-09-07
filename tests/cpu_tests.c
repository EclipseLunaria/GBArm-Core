#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "cpu.h"


void test_set_flag(){
    uint32_t cspr = 0;
    CSPR_set_flag(A,1, &cspr);
    CU_ASSERT_TRUE(cspr&A);
    CU_ASSERT_FALSE(cspr&N);
}

void test_set_get_flag(){
    uint32_t cspr = 0;

    CSPR_set_flag(A,3, &cspr);
    printf("CSPR: %x", cspr);
    CU_ASSERT_TRUE(CSPR_get_flag(A, &cspr));
    CU_ASSERT_FALSE(CSPR_get_flag(N, &cspr))
}

void test_cpu_init(){
    CPU cpu;
    initCpu(&cpu);
    // check system memory.
    CU_ASSERT_PTR_NOT_NULL(cpu.registers.curRegSet)
    CU_ASSERT_PTR_EQUAL(cpu.registers.curRegSet->pRegisters[0], &cpu.registers.registerData.registers[0])
    CU_ASSERT_EQUAL(cpu.clockCycle, 0)
    CU_ASSERT_EQUAL(cpu.loadedInstruction, 0)
    CU_ASSERT_EQUAL(cpu.sleepCycles, 0)
}


void test_clock_cpu_iteration(){
    CPU cpu;
    initCpu(&cpu);
    CU_ASSERT_EQUAL(cpu.clockCycle, 0);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0);
    clockCpu(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 4);
}   


void test_clock_cpu_load_instruction(){
    CPU cpu;
    initCpu(&cpu);
    word_t testVal = 5555;
    writeWord(0,&testVal);
    CU_ASSERT_EQUAL(cpu.loadedInstruction, 0);
    clockCpu(&cpu);
    CU_ASSERT_EQUAL(cpu.loadedInstruction, testVal)
    CU_ASSERT_EQUAL(*cpu.registers.PC, 4);
}   

int add_cpu_tests(){
    CU_pSuite suite = CU_add_suite("CPU Tests",0,0);

    if (suite == NULL) return CU_get_error();


    if (NULL == CU_add_test(suite, "test set CSRP flag value", test_set_flag)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test set and getting CSRP flag value", test_set_get_flag)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

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