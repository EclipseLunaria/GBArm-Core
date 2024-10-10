#include "core.h"
#include "cpu.h"
#include "instruction.h"

int main(int argc, char *argv[]) {
    CPU cpu;
    init_cpu(&cpu);

    if (argc < 2) {
        printf("ERROR: Please specify the file\n");
        exit(0);
    }
    FILE *in = fopen(argv[1], "r");
    uint32_t size;
    fseek(in, 0, SEEK_END);
    size = ftell(in);

    printf("SIZE: %d\n", size);
    char *buffer = malloc(size);
    instruction_t *instruction_buf = (instruction_t *)buffer;
    fseek(in, 0, SEEK_SET);
    fread(buffer, 1, size, in);
    fclose(in);
    char k = 0;
    while (k != 'q') {
        uint32_t current_instruction = instruction_buf[*cpu.registers.PC / 4];
        printf("\nCurrent Instruction: %x\n", current_instruction);
        execute_instruction(current_instruction, &cpu);
        dump_cpu_state(&cpu);
        printf("\nNEXT INSTRUCTION: %08x\n", instruction_buf[*cpu.registers.PC / 4]);
        k = getchar();
        printf("key: %c\n", k);
    }

    return 0;
}