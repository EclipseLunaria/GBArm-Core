#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include "instruction.h"
#include "alu.h"
#include "cpu.h"
#include "test_macros.h"


void test_direct_branch_call(){
    CPU cpu;
    init_cpu(&cpu);
    uint32_t instruction = 0xEA000007;
    printf("\nPC BEFORE: %x",*cpu.registers.PC);
    B(instruction, &cpu);
    printf("\nPC AFTER: %x",*cpu.registers.PC);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xF)
}

void test_is_mrs_detection(){
    instruction_t mrs_instr = 0xE10F0000;
    instruction_t other_instr = 0xE3A00000;

    CU_ASSERT_TRUE(is_mrs(mrs_instr))
    CU_ASSERT_FALSE(is_mrs(other_instr))
}

void test_MRS_for_CPSR_target_in_user_mode(){
    CPU cpu;
    init_cpu(&cpu);
    //set test flags
    cpu.CPSR->A = 1;
    cpu.CPSR->C = 1;
    cpu.CPSR->Q = 1;
    uint32_t cpsr = cpu.registers.cpsr;
    // MRS R0, CPSR
    MRS(0XE10F0000, &cpu);
    uint32_t rv;
    read_register(0, &cpu.registers, &rv);
    CU_ASSERT_EQUAL(rv, cpsr)

}

void test_MRS_for_CPSR_target_in_privilage_mode(){
    CPU cpu;
    init_cpu(&cpu);
    //set test flags
    cpu.CPSR->A = 1;
    cpu.CPSR->C = 1;
    cpu.CPSR->Q = 1;
    set_mode(1, &cpu.registers);

    uint32_t cpsr = cpu.registers.cpsr;
    // MRS R0, CPSR
    MRS(0XE10F0000, &cpu);
    
    uint32_t rv;
    read_register(0, &cpu.registers, &rv);
    CU_ASSERT_EQUAL(rv, cpsr)
}

void test_MRS_for_SPSR_target_in_privilage_mode(){
    CPU cpu;
    init_cpu(&cpu);
    //set test flags
    cpu.CPSR->A = 1;
    cpu.CPSR->C = 1;
    cpu.CPSR->Q = 1;
    set_mode(1, &cpu.registers);
    cpu.CPSR->A = 0;
    
    // MRS R0, CPSR
    MRS(0xE14F1000, &cpu);

    uint32_t rv;
    read_register(0, &cpu.registers, &rv);
    CU_ASSERT_NOT_EQUAL(rv, *cpu.registers.current_registers->p_spsr)
    
}

void test_MRS_for_SPSR_target_in_user_mode(){
    CPU cpu;
    init_cpu(&cpu);
    //set test flags
    cpu.CPSR->A = 1;
    cpu.CPSR->C = 1;
    cpu.CPSR->Q = 1;
    
    // uint32_t cpsr = cpu.registers.cpsr;
    // MRS R0, CPSR
    MRS(0xE14F1000, &cpu);
    uint32_t rv;
    read_register(1, &cpu.registers, &rv);
    CU_ASSERT_EQUAL(rv, cpu.registers.cpsr)
    
    
}
void test_is_msr_reg(){
    // valid instructions
    // MSR CPSR, r0
    instruction_t valid1 = 0xE12F0000;  // MSR to CPSR
    CU_ASSERT_TRUE(is_msr_reg(valid1));

    // MSR SPSR, r1
    instruction_t valid2 = 0xE13F0010;  // MSR to SPSR
    CU_ASSERT_TRUE(is_msr_reg(valid2));

    // invalid instructions
    // MOV r2, r3
    instruction_t invalid1 = 0xE1A02003;  // MOV instruction
    CU_ASSERT_FALSE(is_msr_reg(invalid1));

    // ADD r4, r5, r6
    instruction_t invalid2 = 0xE0850006;  // ADD instruction
    CU_ASSERT_FALSE(is_msr_reg(invalid2));
}

void test_is_msr_immediate(){
    instruction_t valid_imm1 = 0xE321F000;  // MSR CPSR_f, #0x1F
    CU_ASSERT_TRUE(is_msr_imm(valid_imm1));

    instruction_t valid_imm2 = 0xE367FF00;  // MSR SPSR_cxsf, #0xFF
    CU_ASSERT_TRUE(is_msr_imm(valid_imm2));

    // Invalid instructions
    instruction_t invalid1 = 0xE3A000FF;  // MOV r0, #0xFF
    CU_ASSERT_FALSE(is_msr_imm(invalid1));

    instruction_t invalid2 = 0xE2821001;  // ADD r1, r2, #1
    CU_ASSERT_FALSE(is_msr_imm(invalid2));
}

int add_instruction_tests(){
    CU_pSuite suite = CU_add_suite("Instruction Tests",0,0);

    if (suite == NULL) return CU_get_error();

    ADD_TEST(test_is_mrs_detection)
    ADD_TEST(test_MRS_for_CPSR_target_in_user_mode)
    ADD_TEST(test_MRS_for_CPSR_target_in_privilage_mode)
    ADD_TEST(test_MRS_for_SPSR_target_in_privilage_mode)
    ADD_TEST(test_MRS_for_SPSR_target_in_user_mode)
    ADD_TEST(test_is_msr_reg)
    ADD_TEST(test_is_msr_immediate)
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
