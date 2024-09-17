#include "registers.h"
#include <stdio.h>




int init_registers(CpuRegister * cpuRegister){
    const int size[] = {7,2,2,2,2};
    uint32_t *p_reg_bank[] = {
        cpuRegister->register_data.fiq_registers,
        cpuRegister->register_data.svc_registers,
        cpuRegister->register_data.abt_registers,
        cpuRegister->register_data.irq_registers,
        cpuRegister->register_data.und_registers
    };
    //ensure struct memory is cleared
    memset(cpuRegister, 0, sizeof(*cpuRegister));
    // set program counter and link register
    cpuRegister->PC = &cpuRegister->register_data.registers[15];
    cpuRegister->LR = &cpuRegister->register_data.registers[14];

    // set PC pointers
    for(uint8_t i = 0; i < 6; ++i) {
        cpuRegister->register_sets[i].p_registers[15] = &cpuRegister->register_data.registers[15];
    }
    
    // set lower register pointers
    for(uint8_t i = 0; i < 6; ++i) {
        for (uint8_t j = 0; j < 8; ++j) {
            cpuRegister->register_sets[i].p_registers[j] = &cpuRegister->register_data.registers[j];
        }
    }

    // set user mode register pointers
    for(uint8_t i = 0; i < 16; ++i) {
        cpuRegister->register_sets[0].p_registers[i] = &cpuRegister->register_data.registers[i];
    }

    // set SPSR pointers
    for (int i = 0; i < 6; ++i){
        if (i==0) {
            cpuRegister->register_sets[0].p_spsr = &cpuRegister->cpsr;
            continue;
        }
        cpuRegister->register_sets[i].p_spsr = &cpuRegister->register_data.spsr_registers[i-1];
    }

    // set banked registers
    for (uint8_t i = 0; i<5;i++){
        for (uint8_t j = 0; j<size[i]; ++j) {
            cpuRegister->register_sets[i+1].p_registers[15-size[i]+j] = &p_reg_bank[i][j];
        }
    }
    // init curReg pointer
    cpuRegister->current_registers = &cpuRegister->register_sets[0];

    return 0;

}



int set_mode(uint8_t mode, CpuRegister * cpu_reg){
    mode &= 0xF;
    if (mode >= 6) return -1;
    if (mode == 0 && cpu_reg->current_mode != 0) cpu_reg->cpsr = *cpu_reg->current_registers->p_spsr;
    cpu_reg->current_mode = mode;
    // cpu_reg->current_registers = &cpu_reg->register_sets[mode];
    (*cpu_reg).current_registers = &cpu_reg->register_sets[mode];
    assert(cpu_reg->current_mode != 0 && cpu_reg->current_registers->p_spsr != NULL);
    if (mode != 0) *cpu_reg->current_registers->p_spsr = cpu_reg->cpsr;
    
    return 0;
}
int read_register(uint8_t reg_number, CpuRegister * cpu_reg, uint32_t *buf) {
    if (reg_number >= 16) return -1;
    *buf = *cpu_reg->current_registers->p_registers[reg_number];
    return 0;
}

int read_user_register(uint8_t reg_number, CpuRegister * cpu_reg, uint32_t *buf) {
    if (reg_number >= 16) return -1;
    *buf = cpu_reg->register_data.registers[reg_number];
    return 0;
}

int write_register(uint8_t reg_number, uint32_t value, CpuRegister * cpu_reg){
    if (reg_number >= 16) return -1;
    *cpu_reg->current_registers->p_registers[reg_number] = value;
    return 0;
}
