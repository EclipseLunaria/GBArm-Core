#ifndef REGISTERS_H
#define REGISTERS_H
#include "core.h"


int init_registers(CpuRegister *cpu_register);

int set_mode(uint8_t mode, CpuRegister *cpu_reg);

int read_register(uint8_t reg_number, CpuRegister *cpu_reg, uint32_t *buf);
int write_register(uint8_t reg_number, uint32_t value, CpuRegister *cpu_reg);

int read_user_register(uint8_t reg_number, CpuRegister *cpu_reg, uint32_t *buf);
int write_user_register(uint8_t reg_number, uint32_t value, CpuRegister *cpu_reg);

// register utils
int dump_registers(CPU *cpu);
#endif
