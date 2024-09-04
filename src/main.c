#include "bus.h"
#include <stdio.h>
int main() {
    SystemMemoryMap ram;
    printf("Hello World\n");
    uint8_t in = 10;
    uint8_t out = 0;
    writeByte(0,&in);
    printf("Memory 0: %d", ram.bios[0]);
    uint8_t data = readByte(0, &out);
    printf("\n\n%d, %d\n\n", in, out);


    printf("Hello World\n");
    uint16_t in2 = 6043430;
    uint16_t out2 = 0;
    writeWord(0,&in2);
    printf("Memory 0: %d\n", ram.bios[0]);
    uint8_t data2 = readWord(0, &out2);
    printf("\n\n%d, %d\n\n", in2, out2);
}