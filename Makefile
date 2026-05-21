CC = gcc
CFLAGE = -Wall -Werror
BIN_LOC = ./bin
TARGET = space_game
RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build: main.c
	$(CC) $(CFLAGE) -o $(BIN_LOC)/$(TARGET) main.c $(RAYLIB)

run: main.c
	make build
	./$(BIN_LOC)/$(TARGET)


clean:
	rm -rf bin/*
