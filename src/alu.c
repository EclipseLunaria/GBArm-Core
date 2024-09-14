#include "alu.h"



int ALU_AND(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}

int ALU_EOR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 ^ op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;

}

int ALU_SUB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    
    *result = op1 - op2;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}

int ALU_RSB(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2 - op1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op2_sign != result_sign);
    return 0;
}

int ALU_ADD(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 + op2;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_ADC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
        *result = op1 + op2 + flags->C;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_SBC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 - op2 + flags->C - 1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}

int ALU_RSC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2 - op1;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op2_sign != result_sign);
    return 0;
}

int ALU_TST(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}
int ALU_TEQ(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 ^ op2;
    flags->N = *result >> 31 & 1;
    flags->Z = *result == 0;
    return 0;
}
int ALU_CMP(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 - op2;
    flags->N = (*result >> 31) & 1;
    flags->Z = *result == 0;
    // calc v flag
    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;
    flags->V = (op1_sign != op2_sign) && (op1_sign != result_sign);
    return 0;
}
int ALU_CMN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 + op2;
    
    flags->V = (*result >> 31) & 1;
    flags->Z = *result == 0;

    uint32_t op1_sign = (op1 >> 31) & 1;
    uint32_t op2_sign = (op2 >> 31) & 1;
    uint32_t result_sign = (*result >> 31) & 1;

    flags->V = (op1_sign == op2_sign) && (result_sign != op1);
    return 0;
}

int ALU_ORR(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 | op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_MOV(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_BIC(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = op1 & ~op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}
int ALU_MVN(uint32_t op1, uint32_t op2, BS_FLAGS* flags, uint32_t *result){
    *result = ~op2;
    flags->Z = *result == 0;
    flags->N = (*result >> 31) & 1;
    return 0;
}

int (*aluOp[16])(uint32_t, uint32_t, BS_FLAGS*, uint32_t*) = {
    ALU_AND,
    ALU_EOR,
    ALU_SUB,
    ALU_RSB,
    ALU_ADD,
    ALU_ADC,
    ALU_SBC,
    ALU_RSC,
    ALU_TST,
    ALU_TEQ,
    ALU_CMP,
    ALU_CMN,
    ALU_ORR,
    ALU_MOV,
    ALU_BIC,
    ALU_MVN
};


uint32_t ALU_ROR(uint32_t value, uint8_t shift_amount, CPU* cpu){
    shift_amount %= 32;
    return (value >> shift_amount) | (value << (32 - shift_amount));
}

int eval_register_operand(uint32_t operand_bits, BS_FLAGS *flags, CPU *cpu, uint32_t *result){
    // printf("OP BITS %x", operand_bits);
    uint32_t shift_amount;
    uint32_t rm = operand_bits & 0xF;
    uint8_t is_reg_shift = (operand_bits >> 4 & 1);
    uint8_t rs = (operand_bits >> 8) & 0xF;
    
    uint32_t rm_value;
    
    read_register(rm, &(cpu->registers), &rm_value);
    // printf(" REG VAL: %x", rm_value);
    if (rm == 15) {
        *result = rm_value + 8;
        return 0;
    }

    if (is_reg_shift){
        //Shift by register at bit 8-11
        read_register(rs, &cpu->registers, &shift_amount);
        shift_amount &= 0xFF;
        if (rs == 15) shift_amount += 12;
        if (!shift_amount) flags->C = cpu->CPSR->C;

    }
    else {
        //immediate values
        uint32_t immediate_shift = (operand_bits >> 7) & 0x1F;
        shift_amount = immediate_shift; 
    }
    
    shiftOp[(operand_bits >> 5) & 0b11](rm_value, shift_amount, flags, result);
    return 0;
}

// REFERENCE (4-12): https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf
int alu_execute(uint32_t instruction, CPU *cpu) {
    BS_FLAGS flags;
    
    // handle evaluating op2
    uint32_t op2;
    uint8_t I = (instruction >> 25) & 1;
    if (I){
        // if immediate flag set
        uint8_t rotate = instruction >> 8 & 0xF;
        uint32_t imm = instruction & 0xFF;
        BS_ROR(imm, 2*rotate, &flags, &op2);
    }
    else {
        eval_register_operand(instruction & 0xFFF, &flags, cpu, &op2);
    }

    //evaluate value for output.
    uint32_t reg_output;
    uint8_t opcode = (instruction >> 21) & 0xF;
    // operation register numbers
    uint8_t rn = (instruction >> 16) & 0xF;
    uint32_t rn_value;
    read_register(rn, &cpu->registers,&rn_value);
    // printf("RN: %d, RNVAL: %x, OP2: %x", rn, rn_value, op2);
    aluOp[opcode](rn_value, op2,&flags,&reg_output);
    
    uint8_t writable_operation = (opcode >> 2) != 0b10;
    // printf("WRITABLE: %d, REGV: %x", writable_operation, reg_output);
    
    uint8_t rd = (instruction >> 12) & 0xF;    
    if (writable_operation){
        write_register(rd, reg_output, &cpu->registers);
    }

    // handle writing flags to register
    uint8_t S = (instruction >> 20) & 1;
    if (S) {
        cpu->CPSR->C = flags.C;
        cpu->CPSR->N = flags.N;
        cpu->CPSR->Z = flags.Z;
        if (flags.Is_arithmetic) cpu->CPSR->V = flags.V;
        if (rd == 15) set_mode(0, &cpu->registers);
    }

    return 0;
}