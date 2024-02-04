CC = gcc

CFLAGS = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

EXEC = OwnCalci

SRCS = $(wildcard $(SRC_DIR/*.c))
OBJS = $(pathsubst %.c,%.o,$(SRC))

run:
	@cd $(BIN_DIR) && ./$(EXEC)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

