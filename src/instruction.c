#include "types.h"

#include "core.h"
#include "alu.h"
#include "impl_core.h"
#include "constants.h"
#include "multiply.h"
#include "branch.h"
#include "psr.h"
#include "data_transfer.h"
#include "interrupt.h"

int execute_instruction(instruction_t instruction, CPU *cpu) {
    if (!evaluate_cond((uint8_t)(instruction >> 28), cpu->registers.cpsr)) {
        *cpu->registers.PC += 4;
        return 0;
    };
    if (IS_BRANCH(instruction)) {
        B(instruction, cpu);
    }
    if (IS_MULTIPLY(instruction)) {
        handle_multiply(instruction, cpu);
    }
    if (IS_LONG_MULTIPLY(instruction)) {
        handle_long_multiply(instruction, cpu);
    }
    if (IS_BRANCH_EXCHANGE(instruction)) {
    }
    if (IS_SWAP(instruction)) {
        SWP(instruction, cpu);
    }
    if (IS_HALFWORD_REGISTER_TRANSFER(instruction) || IS_HALFWORD_IMMEDIATE_TRANSFER(instruction) ||
        IS_SIGNED_DATA_TRANSFER(instruction)) {
        STDT(instruction, cpu);
    }

    if (IS_REGISTER_MSR(instruction)) {
        MSR_REG(instruction, cpu);
    }
    if (IS_MRS_OPERATION(instruction)) {
        MRS(instruction, cpu);
    }

    if (IS_ALU_OPERTAION(instruction)) {
        alu_execute(instruction, cpu);
    }
    if (IS_LOAD_STORE_REGISTER_UBYTE(instruction)) {
        SDT(instruction, cpu);
    }
    // if (IS_UNDEFINED(instruction)) {
    //     return decode_undefined;
    // }
    if (IS_BLOCK_DATA_TRANSFER(instruction)) {
        BDT(instruction, cpu);
    }
    // if (IS_COPROCESSOR_DATA_TRANSFER(instruction)) {
    //     return decode_coprocessor_data_transfer;
    // }
    // if (IS_COPROCESSOR_DATA_OPERATION(instruction)) {
    //     return decode_coprocessor_data_operation;
    // }
    // if (IS_COPROCESSOR_REGISTER_TRANSFER(instruction)) {
    //     return decode_coprocessor_register_transfer;
    // }
    if (IS_SOFTWARE_INTERRUPT(instruction)) {
        return SWI(instruction, cpu);
    }
    *cpu->registers.PC += 4;
    return 0;
}


