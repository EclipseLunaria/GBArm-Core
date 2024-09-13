CC = gcc
CFLAGS = -Iinclude -Wall -Werror
SRC = src/bus.c src/utils.c src/cpu.c src/assembler.c src/registers.c src/barrel_shifter.c src/instruction.c src/alu.c src/main.c
HEADERS = include/bus.h include/utils.h include/cpu.h include/assembler.h include/registers.h include/barrel_shifter.h include/types.h include/alu.h include/core.h include/core.h
TARGET = Main

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

test:
	$(MAKE) -C tests run_tests  # Calls the 'test' target in the tests directory