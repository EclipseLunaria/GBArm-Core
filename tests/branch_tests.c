#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "test_macros.h"
#include "core.h"
#include "../internal/registers.h"
#include "types.h"

void test_basic_link_branch(){
	// bug discovered running gba boot bios
	CPU cpu;
	init_cpu(&cpu);
	
	uint32_t instruction = 0xea000018;
	uint32_t expected = 0x4;

	execute_instruction(instruction, &cpu);
	CU_ASSERT_EQUAL(*cpu.registers.PC, 0x68)
	CU_ASSERT_EQUAL(*cpu.registers.LR, 0x4)
	
}
int add_branch_tests(){
	CU_pSuite suite = CU_add_suite("Branch Instruction Tests",0,0);
	if (suite == NULL) return CU_get_error();
	
	ADD_TEST(test_basic_link_branch)
	return CUE_SUCCESS;	
}
