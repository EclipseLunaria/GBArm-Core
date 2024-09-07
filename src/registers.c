#include "registers.h"
#include <stdio.h>




int initCpuRegisters(CpuRegister * cpuRegister){
    const int size[] = {7,2,2,2,2};
    uint32_t *pRegBank[] = {
        cpuRegister->registerData.fiqRegisters,
        cpuRegister->registerData.svcRegisters,
        cpuRegister->registerData.abtRegisters,
        cpuRegister->registerData.irqRegisters,
        cpuRegister->registerData.undRegisters
    };
    //ensure struct memory is cleared
    memset(cpuRegister, 0, sizeof(*cpuRegister));
    // set program counter
    cpuRegister->PC = &cpuRegister->registerData.registers[15];
    cpuRegister->LR = &cpuRegister->registerData.registers[14];
    for(uint8_t i = 0; i < 6; ++i) cpuRegister->regSets[i].pRegisters[15] = &cpuRegister->registerData.registers[15];
    
    for(uint8_t i = 0; i < 6; ++i) {
        for (uint8_t j = 0; j < 8; ++j) cpuRegister->regSets[i].pRegisters[j] = &cpuRegister->registerData.registers[j];
    }

    // set register pointers
    for(uint8_t i = 0; i < 16; ++i) cpuRegister->regSets[0].pRegisters[i] = &cpuRegister->registerData.registers[i];
    for (uint8_t i = 0; i<5;i++){
        for (uint8_t j = 0; j<size[i]; ++j) cpuRegister->regSets[i+1].pRegisters[15-size[i]+j] = &pRegBank[i][j];
    }
    // init curReg pointer
    cpuRegister->curRegSet = &cpuRegister->regSets[0];

    return 0;

}

void dumpRegisterSet(RegisterSet regSet){
    printf("register dump: \n");
    for (uint8_t i = 0; i < 16; ++i){
        printf("%d\n", i);
        printf("register %d: %p -> %d\n", i, regSet.pRegisters[i],*regSet.pRegisters[i]);
    }
}


int setMode(uint8_t mode, CpuRegister * cpuReg){
    if (mode >= 6) return -1;
    cpuReg->currentMode = mode;
    (*cpuReg).curRegSet = &cpuReg->regSets[mode];
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
