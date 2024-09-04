CC = gcc
CFLAGS = -Iinclude -Wall -Werror
SRC = src/bus.c src/main.c
HEADERS = include/bus.h include/types.h
TARGET = Main

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

test:
	$(MAKE) -C tests run_tests  # Calls the 'test' target in the tests directory