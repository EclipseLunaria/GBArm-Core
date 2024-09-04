CC = gcc
CFLAGS = -Iinclude -Wall
OBJ = src/main.o src/bus.o

TARGET = project

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)