CC = gcc

SHELL := cmd.exe

CFLAGS = -Iinclude

LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

TARGET = game.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /Q build\*.o
	-del /Q $(TARGET)