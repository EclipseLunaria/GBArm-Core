#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "test_macros.h"
#include "core.h"

#include "alu.h"
#include "registers.h"

void test_AND_no_shift(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x10;
    uint32_t expected = 0x10;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_AND_negative(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x80000000;
    uint32_t op2 = 0xF0000000;
    uint32_t expected = 0x80000000;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_TRUE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_AND_start_non_zero_to_zero(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x0;
    uint32_t op2 = 0xFFFFF;
    uint32_t expected = 0x0;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_AND_pass_c_flag(){
    BS_FLAGS flags;
    flags.C = 1;

    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x0F;
    uint32_t expected = 0x0;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}

void test_EOR_no_shift(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF;
    uint32_t op2 = 0x1;
    uint32_t expected = 0x1;
    ALU_AND(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_EOR_negative(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x80000000;
    uint32_t op2 = 0xE0000000;
    uint32_t expected = 0xF0000000;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_TRUE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_EOR_start_non_zero_to_zero(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF;
    uint32_t op2 = 0xF;
    uint32_t expected = 0x0;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_TRUE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}
void test_EOR_pass_c_flag(){
    BS_FLAGS flags;
    flags.C = 1;

    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x0F;
    uint32_t expected = 0xFF;
    ALU_EOR(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.C)
    CU_ASSERT_FALSE(flags.N)
    CU_ASSERT_FALSE(flags.V)
    CU_ASSERT_FALSE(flags.Z)
    CU_ASSERT_FALSE(flags.Is_arithmetic)
}

void test_SUB_basic(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0xF0;
    uint32_t op2 = 0x10;
    uint32_t expected = 0xE0;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Positive result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_negative_result(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x10;
    uint32_t op2 = 0x20;
    uint32_t expected = 0xFFFFFFF0; // -16 in 2's complement
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_TRUE(flags.N)   // Negative result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_zero_result(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x20;
    uint32_t op2 = 0x20;
    uint32_t expected = 0x0;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Not negative
    CU_ASSERT_TRUE(flags.Z)   // Result is zero
}

void test_SUB_signed_overflow(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x7FFFFFFF;  // -2147483648 in signed 32-bit
    uint32_t op2 = 0xFFFFFFFF;  // -1
    uint32_t expected = 0x80000000;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_TRUE(flags.V)   // Signed overflow
    CU_ASSERT_TRUE(flags.N)   // Negative result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

void test_SUB_no_overflow(){
    BS_FLAGS flags;
    uint32_t result;
    uint32_t op1 = 0x7FFFFFFF;  // 2147483647 in signed 32-bit
    uint32_t op2 = 0x00000001;  // 1
    uint32_t expected = 0x7FFFFFFE;
    ALU_SUB(op1, op2, &flags, &result);
    // assert result
    CU_ASSERT_EQUAL(result, expected)
    // assert flags
    CU_ASSERT_FALSE(flags.V)  // No overflow
    CU_ASSERT_FALSE(flags.N)  // Positive result
    CU_ASSERT_FALSE(flags.Z)  // Result is non-zero
}

// Register specified shift amount tests 
// https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf 4-14

// Only the least significant byte of the contents of Rs is used to determine the shift
// amount. Rs can be any general register other than R15. 
void test_eval_operand2(){
    // int eval_register_operand(uint32_t operandBits, BS_FLAGS *flags, CpuRegister *reg, uint32_t *result)
    CPU cpu;
    init_cpu(&cpu);
    BS_FLAGS flags;
    //set register to 
    uint32_t result;
    uint32_t expected = 4;
    uint32_t operandBits = 0x214;
    write_register(2, 1,&cpu.registers);
    write_register(4, 0x2, &cpu.registers);

    eval_register_operand(operandBits, &flags, &cpu, &result);
    CU_ASSERT_EQUAL(result, expected)
    
}
void test_eval_operand2_get_least_sig_byte(){
    // int eval_register_operand(uint32_t operandBits, BS_FLAGS *flags, CpuRegister *reg, uint32_t *result)
    CPU cpu;
    init_cpu(&cpu);
    BS_FLAGS flags;
    //set register to 
    uint32_t result;
    uint32_t expected = 4;
    uint32_t operandBits = 0x214;
    write_register(2, 0xE01,&cpu.registers); // only read least significant 
    write_register(4, 0x2, &cpu.registers);

    eval_register_operand(operandBits, &flags, &cpu, &result);
    CU_ASSERT_EQUAL(result, expected)
    
}

// test PC as operand
void test_eval_operand_with_pc_with_rm(){
    CPU cpu;
    init_cpu(&cpu);
    BS_FLAGS flags;
    uint32_t opBits = 0xF0F;
    uint32_t actual;
    uint32_t expected = 0x17;
    *cpu.registers.PC = 0xF;
    eval_register_operand(opBits, &flags, &cpu, &actual);
    CU_ASSERT_EQUAL(actual, expected)

}
void test_eval_operand_with_rs_as_pc(){
    CPU cpu;
    init_cpu(&cpu);
    BS_FLAGS flags;

    uint32_t opBits = 0xF11;
    write_register(1, 1, &cpu.registers);
    uint32_t actual;
    uint32_t expected = 0x10000;
    *cpu.registers.PC = 0x4;
    
    eval_register_operand(opBits, &flags, &cpu, &actual);

    CU_ASSERT_EQUAL(actual, expected)

}

// test executeALU
void test_execute_alu_immediate_no_rotate(){
    CPU cpu;
    init_cpu(&cpu);
    uint32_t cond = 0xE;
    flag_t I = 1;
    uint8_t opCode = 0;
    flag_t S = 0;
    reg_t rn = 0;
    reg_t rd = 1;
    // init register values
    uint32_t rnVal = 0xFF;
    uint32_t rdVal;
    write_register(rn, rnVal, &cpu.registers);
    // op2
    uint8_t rotate = 0x0;
    uint8_t imm = 0xF;
    uint32_t immOp = (rotate << 8) | imm;

    uint32_t instruction = 
      (cond << 28)
    | (I << 25)
    | (opCode << 21)
    | (S << 20)
    | (rn << 16)
    | (rd << 12)
    | (immOp); 
    alu_execute(instruction, &cpu);
    read_register(rd, &cpu.registers, &rdVal);
    CU_ASSERT_EQUAL(rdVal, 0xF)
}


int add_alu_tests(){
    CU_pSuite suite = CU_add_suite("ALU Tests",0,0);

    if (suite == NULL) return CU_get_error();

    ADD_TEST(test_AND_negative )
    ADD_TEST(test_AND_no_shift )
    ADD_TEST(test_AND_pass_c_flag )
    ADD_TEST(test_AND_start_non_zero_to_zero)
    ADD_TEST(test_EOR_no_shift)
    ADD_TEST(test_EOR_start_non_zero_to_zero)
    ADD_TEST(test_EOR_pass_c_flag )

    // sub 
    ADD_TEST(test_SUB_basic);
    ADD_TEST(test_SUB_negative_result);
    ADD_TEST(test_SUB_zero_result);
    ADD_TEST(test_SUB_signed_overflow);
    ADD_TEST(test_SUB_no_overflow);

    // test eval_register_operand
    ADD_TEST(test_eval_operand2)
    ADD_TEST(test_eval_operand2_get_least_sig_byte)
    ADD_TEST(test_eval_operand_with_pc_with_rm)
    ADD_TEST(test_eval_operand_with_rs_as_pc)
    ADD_TEST(test_execute_alu_immediate_no_rotate)
    // Register specified shift amount tests 
    return CUE_SUCCESS;
}
