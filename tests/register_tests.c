#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "registers.h"


void test_register_init_pc_pointer(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_PTR_EQUAL(reg.PC, &reg.registerData.registers[15])
    CU_ASSERT_PTR_NULL(reg.regSets[0].pSpsr)
    CU_ASSERT_EQUAL(reg.cpsr, 0)
}

void test_register_init_values(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_EQUAL(reg.registerData.registers[0], 0)
    CU_ASSERT_EQUAL(reg.registerData.registers[15], 0)
}

void test_user_register_pointers() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    for (uint8_t i = 0; i < 16; ++i) CU_ASSERT_PTR_EQUAL(reg.regSets[0].pRegisters[i], &reg.registerData.registers[i]);
}

void test_fiq_pointer_register_init() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_PTR_EQUAL(reg.regSets[1].pRegisters[8], &reg.registerData.fiqRegisters[0])
    CU_ASSERT_PTR_EQUAL(reg.PC, reg.regSets[1].pRegisters[15])
}

void test_fiq_register_bank_pointer_initialized() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_NOT_EQUAL(reg.regSets[0].pRegisters[8], reg.regSets[1].pRegisters[8])
}

void test_fiq_save_bank_pointers() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    reg.registerData.registers[8] = 10;
    CU_ASSERT_EQUAL(*reg.regSets[0].pRegisters[8], 10)
    CU_ASSERT_NOT_EQUAL(*reg.regSets[1].pRegisters[8], 10)
}

void test_current_register_initialize() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_PTR_NOT_NULL(reg.curRegSet)
    CU_ASSERT_PTR_EQUAL(&reg.regSets[0],reg.curRegSet)
}

void test_write_default_register() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    writeRegister(2, 100, &reg);
    CU_ASSERT_EQUAL(100, reg.registerData.registers[2])
    CU_ASSERT_EQUAL(100, *reg.curRegSet->pRegisters[2])
}

void test_read_default_register() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    reg.registerData.registers[4] = 66;
    uint32_t value;
    readRegister(4, &reg,&value);
    CU_ASSERT_EQUAL(value, 66)

}

void test_write_read_default_register() {
    CpuRegister reg;
    initCpuRegisters(&reg);
    writeRegister(2, 100, &reg);
    uint32_t regValue;
    readRegister(2, &reg, &regValue);
    CU_ASSERT_EQUAL(100, regValue)
}

void test_current_reg_pointer_after_mode_set(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    RegisterSet *pStart = &*reg.curRegSet;
    setMode(1, &reg);
    CU_ASSERT_PTR_NOT_EQUAL(reg.curRegSet, pStart)
}

void test_write_mode_set_then_read_on_banked_register(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    uint32_t first;
    uint32_t second;
    writeRegister(9, 5050, &reg);
    readRegister(9, &reg, &first);
    CU_ASSERT_EQUAL(first, 5050)
    setMode(1, &reg);

    CU_ASSERT_NOT_EQUAL(second, first)

}

void test_write_mode_set_then_read_on_default_register(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    uint32_t first;
    uint32_t second;
    writeRegister(5, 5050, &reg);
    readRegister(5, &reg, &first);
    setMode(1, &reg);
    readRegister(5, &reg, &second);
    CU_ASSERT_EQUAL(second, first)

}

void test_register_value_init(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    byte_t * p = (byte_t *)&reg.registerData;
    for (int i; i < sizeof(Registers); ++i,++p){
        CU_ASSERT_EQUAL(*p, 0)
    }
}

void test_register_init_pc_and_lr(){
    CpuRegister reg;
    initCpuRegisters(&reg);
    CU_ASSERT_EQUAL(*reg.LR, reg.registerData.registers[14])
    CU_ASSERT_EQUAL(*reg.PC, reg.registerData.registers[15])
}

int add_register_tests(){
    CU_pSuite suite = CU_add_suite("Register Tests",0,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test init register values", test_register_value_init)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test init PC pointer", test_register_init_pc_pointer)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test init register values", test_register_init_values)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test init user register pointers", test_user_register_pointers)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test init fiq register pointers", test_fiq_pointer_register_init)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test init fiq register bank values", test_fiq_save_bank_pointers)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test current register init", test_current_register_initialize)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    

    if (NULL == CU_add_test(suite, "test write normal register in default mode", test_write_default_register)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    
    if (NULL == CU_add_test(suite, "test write then read normal register in default mode", test_write_read_default_register)) {
        CU_cleanup_registry();
        return CU_get_error();
    }



    if (NULL == CU_add_test(suite, "test read normal register in default mode", test_read_default_register)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(suite, "test cur register pointer after mode switch", test_current_reg_pointer_after_mode_set)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(suite, "test write-modeset read on banked register", test_write_mode_set_then_read_on_banked_register)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(suite, "test  fiq register bank pointer initialized", test_fiq_register_bank_pointer_initialized)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(suite, "test register init pc and lr", test_register_init_pc_and_lr)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    
   
    

    return CUE_SUCCESS;
}