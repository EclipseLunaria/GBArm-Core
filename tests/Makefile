# Project Makefile (Root Makefile)

CC = gcc
CFLAGS = -I../include -Wall -Werror -lcunit
SRC = ../src/bus.c ../src/cpu.c bus_tests.c cpu_tests.c main_test_runner.c
HEADERS = ../include/bus.h ../include/cpu.h ../include/types.h 
TARGET = run_tests

# Build the main project executable
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	$(MAKE) -C tests clean  # Calls the clean target in the tests directory

# To run tests from the root directory
