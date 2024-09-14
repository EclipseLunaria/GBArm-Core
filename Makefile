CC = gcc
CFLAGS = -Iinclude -Wall -Werror
# SRC = src/bus.c src/utils.c src/cpu.c src/assembler.c src/repl.c src/registers.c src/barrel_shifter.c src/instruction.c src/alu.c src/main.c
# HEADERS =  include/core.h include/constants.h include/bus.h include/utils.h include/cpu.h include/assembler.h include/repl.h include/registers.h include/barrel_shifter.h include/types.h include/alu.h
TARGET = Main
SRC = src/main.c src/cpu.c src/registers.c src/bus.c src/repl.c src/utils.c src/alu.c src/assembler.c src/constants.c src/barrel_shifter.c
HEADERS = include/core.h include/cpu.h include/registers.h include/types.h include/bus.h include/repl.h include/utils.h include/alu.h include/assembler.h include/constants.h include/barrel_shifter.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

test:
	$(MAKE) -C tests run_tests  # Calls the 'test' target in the tests directory