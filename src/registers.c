#include "registers.h"
#include <stdio.h>

int initCpuRegisters(CpuRegister * cpuRegister){
   
    // set program counter
    memset(cpuRegister, 0, sizeof(*cpuRegister));
    

    dumpRegisterSet(cpuRegister->regSets[0]);
    return 0;
}

void dumpRegisterSet(RegisterSet regSet){
    printf("register dump: \n");
    for (uint8_t i = 0; i < 16; ++i){
        printf("%d\n", i);
        printf("register %d: %p -> \n", i, regSet.pRegisters[i]);
    }
}


int setMode(uint8_t mode, CpuRegister * cpuReg){
    if (mode <= 6) return -1;
    cpuReg->currentMode = mode;
    cpuReg->curRegSet = &cpuReg->regSets[mode];
    return 0;
}
int readRegister(uint8_t regNum, CpuRegister * cpuReg, uint32_t *buf) {
    if (regNum >= 16) return -1;
    *buf = *cpuReg->curRegSet->pRegisters[regNum];
    return 0;
}
int writeRegister(uint8_t regNum, uint32_t value, CpuRegister * cpuReg){
    if (regNum >= 16) return -1;
    *cpuReg->curRegSet->pRegisters[regNum] = value;
    return 0;
}
