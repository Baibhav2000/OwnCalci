CC = gcc

CFLAGS = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

EXEC = $(BIN_DIR)/OwnCalci

SRCS = $(wildcard $(SRC_DIR/*.c))
OBJS = $(pathsubst %.c,%.o,$(SRC))

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

