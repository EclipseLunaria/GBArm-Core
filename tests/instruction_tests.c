#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "instruction.h"
#include "alu.h"
#include "cpu.h"

int evaluateRegOperand(uint16_t regOpcode, CPU *cpu, uint32_t *value);

void test_direct_branch_call(){
    CPU cpu;
    initCpu(&cpu);
    cpu.loadedInstruction = 0xEA000007;
    printf("\nPC BEFORE: %x",*cpu.registers.PC);
    B(&cpu);
    printf("\nPC AFTER: %x",*cpu.registers.PC);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xF)
}

void test_double_branch_and_load(){
    uint32_t jump1 = 0xEA000007;
    uint32_t jump2 = 0xEA000004;
    writeWord(0, &jump1);
    writeWord(0xF, &jump2);
    CPU cpu;
    initCpu(&cpu);
    cpu.ram.bios[0] = jump1;
    clockCpu(&cpu);
    B(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xF)
    clockCpu(&cpu);
    B(&cpu);
    CU_ASSERT_EQUAL(*cpu.registers.PC, 0xC)

}

void test_alu_decode(){
    uint32_t jump1 = 0xE1A020A0;
    ALUInstruction aluInstruction;
    decodeALUInstruction(jump1, &aluInstruction);
    printf("ALU INSTRUCTION(cond:%x, IFlag:%x, Opcode:%x, setCodes:%x, rn:%x, rd:%x):", aluInstruction.cond, aluInstruction.IFlag, aluInstruction.opcode, aluInstruction.setCodes,aluInstruction.rn, aluInstruction.rd);

    CU_ASSERT_EQUAL(aluInstruction.cond, 0xE)
    CU_ASSERT_EQUAL(aluInstruction.rd, 0x2)
    CU_ASSERT_EQUAL(aluInstruction.rn, 0x0)
    CU_ASSERT_EQUAL(aluInstruction.setCodes, 0x0)
}

void test_register_and_operand(){
    uint32_t jump1 = 0xE1A020A0;
    ALUInstruction aluInstruction;
    decodeALUInstruction(jump1, &aluInstruction);
    printf("ALU INSTRUCTION(cond:%x, IFlag:%x, Opcode:%x, setCodes:%x, rn:%x, rd:%x):", aluInstruction.cond, aluInstruction.IFlag, aluInstruction.opcode, aluInstruction.setCodes,aluInstruction.rn, aluInstruction.rd);

    CU_ASSERT_EQUAL(aluInstruction.cond, 0xE)
    CU_ASSERT_EQUAL(aluInstruction.rd, 0x2)
    CU_ASSERT_EQUAL(aluInstruction.rn, 0x0)
    CU_ASSERT_EQUAL(aluInstruction.setCodes, 0x0)
}

void test_eval_register_operand_no_shift(){
    CPU cpu;
    initCpu(&cpu);
    uint16_t op2Code = 0x005;
    uint32_t expected = 420710;
    writeRegister(0x5, expected, &cpu.registers);
    uint32_t actual;
    evaluateRegOperand(op2Code, &cpu, &actual);
    CU_ASSERT_EQUAL(actual, expected)
}



int add_instruction_tests(){
    CU_pSuite suite = CU_add_suite("Instruction Tests",0,0);

    if (suite == NULL) return CU_get_error();

    if (NULL == CU_add_test(suite, "test direct branch call", test_direct_branch_call)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test double branch and load", test_double_branch_and_load)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test alu decode", test_alu_decode)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    if (NULL == CU_add_test(suite, "test eval register operand no shift", test_eval_register_operand_no_shift)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    return CUE_SUCCESS;
}