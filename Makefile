# Makefile for the project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Binary name
BIN_NAME = $(BIN_DIR)/OwnCalci

# Default target
all: directories $(BIN_NAME)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the binary
$(BIN_NAME): $(OBJ_FILES)
	$(CC) $^ -o $@

# Run the binary
run: $(BIN_NAME)
	./$(BIN_NAME)

# Clean up the generated files
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean
