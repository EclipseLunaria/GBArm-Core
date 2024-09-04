#include "bus.h"
#include <stdio.h>
int main() {
    SystemMemoryMap * ram = &DATA_BUS;
    printf("Hello World\n");
    uint8_t in = 10;
    uint8_t out = 0;
    writeByte(0,&in);
    printf("Memory 0: %d", (*ram).bios[0]);
    readByte(0, &out);
    printf("\n\n%d, %d\n\n", in, out);


    printf("Hello World\n");
    uint32_t in2 = 6043430;
    uint32_t out2 = 0;
    writeWord(0,&in2);
    printf("Memory 0: %d\n", (*ram).bios[0]);
    readWord(0, &out2);
    printf("\n\n%d, %d\n\n", in2, out2);
    return 0;
}