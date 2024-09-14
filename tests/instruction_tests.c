#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "instruction.h"
#include "alu.h"
#include "cpu.h"


void test_direct_branch_call(){
    CPU cpu;
    init_cpu(&cpu);
    cpu.loaded_instruction = 0xEA000007;
    printf("\nPC BEFORE: %x",*cpu.registers.PC);
    B(&cpu);
    printf("\nPC AFTER: %x",*cpu.registers.PC);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xF)
}

void test_double_branch_and_load(){
    uint32_t jump1 = 0xEA000007;
    uint32_t jump2 = 0xEA000004;
    write_word(0, &jump1);
    write_word(0xF, &jump2);
    CPU cpu;
    init_cpu(&cpu);
    cpu.ram.bios[0] = jump1;
    clock_cpu(&cpu);
    B(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xF)
    clock_cpu(&cpu);
    B(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xC)

}

// void test_eval_register_operand_no_shift(){
//     CPU cpu;
//     init_cpu(&cpu);
//     uint16_t op2Code = 0x005;
//     uint32_t expected = 420710;
//     write_register(0x5, expected, &cpu.registers);
//     uint32_t actual;
//     evaluateRegOperand(op2Code, &cpu, &actual);
//     CU_ASSERT_EQUAL(actual, expected)
// }



int add_instruction_tests(){
    CU_pSuite suite = CU_add_suite("Instruction Tests",0,0);

    if (suite == NULL) return CU_get_error();

    // if (NULL == CU_add_test(suite, "test direct branch call", test_direct_branch_call)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }

    // if (NULL == CU_add_test(suite, "test double branch and load", test_double_branch_and_load)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }


    // if (NULL == CU_add_test(suite, "test eval register operand no shift", test_eval_register_operand_no_shift)) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }
    

    return CUE_SUCCESS;
}