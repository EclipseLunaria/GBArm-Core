#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "test_macros.h"
#include "core.h"
#include "../internal/registers.h"
#include "types.h"

void test_load_register_to_pc(){
	// bug discovered running gba boot bios
	CPU cpu;
	init_cpu(&cpu);
	
	uint32_t instruction = 0xe129f000;
	uint32_t expected = 0xdf;
	//set register values
	write_register(0, 0xdf, &cpu.registers);
	write_register(12, 0x4000000, &cpu.registers);
	write_register(14, 0x4, &cpu.registers);
	write_register(15, 0x94, &cpu.registers);

	execute_instruction(instruction, &cpu);
	CU_ASSERT_EQUAL(cpu.registers.cpsr, 0xdf);
	CU_ASSERT_EQUAL(*cpu.registers.PC, 0x94);
}
int add_psr_tests(){
	CU_pSuite suite = CU_add_suite("PSR Function Tests",0,0);
	if (suite == NULL) return CU_get_error();
	
	ADD_TEST(test_load_register_to_pc)
	return CUE_SUCCESS;	
}
