#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../internal/registers.h"
#include "test_macros.h"

void test_register_init_pc_pointer(){
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_PTR_EQUAL(reg.PC, &reg.register_data.registers[15])
    CU_ASSERT_EQUAL(reg.register_sets[0].p_spsr, &reg.cpsr)
    CU_ASSERT_EQUAL(reg.cpsr, 0)
}

void test_register_init_values(){
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_EQUAL(reg.register_data.registers[0], 0)
    CU_ASSERT_EQUAL(reg.register_data.registers[15], 0)
}

void test_user_register_pointers() {
    CpuRegister reg;
    init_registers(&reg);
    for (uint8_t i = 0; i < 16; ++i) CU_ASSERT_PTR_EQUAL(reg.register_sets[0].p_registers[i], &reg.register_data.registers[i]);
}

void test_fiq_pointer_register_init() {
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_PTR_EQUAL(reg.register_sets[1].p_registers[8], &reg.register_data.fiq_registers[0])
    CU_ASSERT_PTR_EQUAL(reg.PC, reg.register_sets[1].p_registers[15])
}

void test_fiq_register_bank_pointer_initialized() {
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_NOT_EQUAL(reg.register_sets[0].p_registers[8], reg.register_sets[1].p_registers[8])
}

void test_fiq_save_bank_pointers() {
    CpuRegister reg;
    init_registers(&reg);
    reg.register_data.registers[8] = 10;
    CU_ASSERT_EQUAL(*reg.register_sets[0].p_registers[8], 10)
    CU_ASSERT_NOT_EQUAL(*reg.register_sets[1].p_registers[8], 10)
}

void test_current_register_initialize() {
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_PTR_NOT_NULL(reg.current_registers)
    CU_ASSERT_PTR_EQUAL(&reg.register_sets[0],reg.current_registers)
}

void test_write_default_register() {
    CpuRegister reg;
    init_registers(&reg);
    write_register(2, 100, &reg);
    CU_ASSERT_EQUAL(100, reg.register_data.registers[2])
    CU_ASSERT_EQUAL(100, *reg.current_registers->p_registers[2])
}

void test_read_default_register() {
    CpuRegister reg;
    init_registers(&reg);
    reg.register_data.registers[4] = 66;
    uint32_t value;
    read_register(4, &reg,&value);
    CU_ASSERT_EQUAL(value, 66)

}

void test_write_read_default_register() {
    CpuRegister reg;
    init_registers(&reg);
    write_register(2, 100, &reg);
    uint32_t regValue;
    read_register(2, &reg, &regValue);
    CU_ASSERT_EQUAL(100, regValue)
}



void test_write_mode_set_then_read_on_default_register(){
    CpuRegister reg;
    init_registers(&reg);
    uint32_t first;
    uint32_t second;
    write_register(5, 5050, &reg);
    read_register(5, &reg, &first);
    set_mode(1, &reg);
    read_register(5, &reg, &second);
    CU_ASSERT_EQUAL(second, first)

}

void test_register_value_init(){
    CpuRegister reg;
    init_registers(&reg);
    byte_t * p = (byte_t *)&reg.register_data;
    for (int i; i < sizeof(Registers); ++i,++p){
        CU_ASSERT_EQUAL(*p, 0)
    }
}

void test_register_init_pc_and_lr(){
    CpuRegister reg;
    init_registers(&reg);
    CU_ASSERT_EQUAL(*reg.LR, reg.register_data.registers[14])
    CU_ASSERT_EQUAL(*reg.PC, reg.register_data.registers[15])
}

int add_register_tests(){
    CU_pSuite suite = CU_add_suite("Register Tests",0,0);

    if (suite == NULL) return CU_get_error();

	ADD_TEST(test_register_value_init)
	ADD_TEST(test_register_init_pc_pointer)
	ADD_TEST(test_register_init_values)
	ADD_TEST(test_user_register_pointers)
	ADD_TEST(test_fiq_pointer_register_init)
	ADD_TEST(test_fiq_save_bank_pointers)
    ADD_TEST(test_current_register_initialize)
	ADD_TEST(test_write_default_register)	
	ADD_TEST(test_write_read_default_register)
    ADD_TEST(test_read_default_register)
	ADD_TEST(test_fiq_register_bank_pointer_initialized)
    ADD_TEST(test_register_init_pc_and_lr)

    
   
    

    return CUE_SUCCESS;
}
