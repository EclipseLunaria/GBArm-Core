#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "cpu.h"
#include "test_macros.h"

void test_cpu_init() {
    CPU cpu;
    init_cpu(&cpu);
    // check system memory.
    CU_ASSERT_PTR_NOT_NULL(cpu.registers.current_registers)
    CU_ASSERT_PTR_EQUAL(cpu.registers.current_registers->p_registers[0], &cpu.registers.register_data.registers[0])
    CU_ASSERT_EQUAL(cpu.clock_cycles, 0)
    CU_ASSERT_EQUAL(cpu.loaded_instruction, 0)
    CU_ASSERT_EQUAL(cpu.sleep_cycles, 0)
}



void test_spsr_cpu_init() {
    CPU cpu;
    init_cpu(&cpu);
    for (int i = 0; i < 5; ++i) {
        CU_ASSERT_PTR_NOT_NULL(cpu.registers.current_registers->p_spsr)
    }
}

int add_cpu_tests() {
    CU_pSuite suite = CU_add_suite("CPU Tests", 0, 0);

    if (suite == NULL) return CU_get_error();

    ADD_TEST(test_spsr_cpu_init)

    if (NULL == CU_add_test(suite, "test init cpu", test_cpu_init)) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    return CUE_SUCCESS;
}