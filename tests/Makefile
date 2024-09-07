# Project Makefile (Root Makefile)

CC = gcc
CFLAGS = -I../include -Wall -Werror -lcunit
SRC = ../src/bus.c ../src/cpu.c ../src/registers.c ../src/instruction.c bus_tests.c cpu_tests.c cond_tests.c register_tests.c main_test_runner.c 
HEADERS = ../include/bus.h ../include/cpu.h ../include/registers.h ../include/types.h ../include/core.h ../include/core.h ../include/instruction.h
TARGET = run_tests

# Build the main project executable

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	$(MAKE) -C tests clean  # Calls the clean target in the tests directory

# To run tests from the root directory
