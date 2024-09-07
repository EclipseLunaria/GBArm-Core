#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "core.h"
#include "alu.h"

// REGISTER ALU

// TEST ALU OPS

void test_and_op_no_shift_register(){
    CPU cpu;
    initCpu(&cpu);
    int rn = 0xF;
    int rm = 0x3;
    int opcode = 0x0;

    CU_ASSERT_EQUAL(aluOp[opcode](rn,rm,&cpu), 0x3)
}

void test_and_op_no_shift_large_number(){
    CPU cpu;
    initCpu(&cpu);
    int rn = 0xFFFFFF;
    int rm = 0x222222;
    int opcode = 0x0;

    CU_ASSERT_EQUAL(aluOp[opcode](rn,rm,&cpu), 0x222222)
}


int add_alu_tests(){
    CU_pSuite suite = CU_add_suite("ALU Tests",0,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test and op no shift register", test_and_op_no_shift_register)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test and op no shift register large number", test_and_op_no_shift_large_number)) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    return CUE_SUCCESS;
}