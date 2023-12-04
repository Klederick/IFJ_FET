CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = obj

# List of source files (replace these with your source files)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Create a list of object files based on source files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# The final executable
TARGET = compiler

stack: src/stack.c
	$(CC) $(CFLAGS) -o $@ $<

remove_st:
	rm -f stack

main: src/main.c
	$(CC) $(CFLAGS) -o $@ $<

remove_ma:
	rm -f main

expression: src/expression.c
	$(CC) $(CFLAGS) -o $@ $<

remove_ex:
	rm -f expression

error: src/error.c
	$(CC) $(CFLAGS) -o $@ $<

remove_er:
	rm -f error

dynamic: src/dynamic.c
	$(CC) $(CFLAGS) -o $@ $<

dynamicval: src/dynamic.c
	$(CC) $(CFLAGS) -g -o $@ $<

remove_dy:
	rm -f dynamic

remove_dyval:
	rm -f dynamicval

gen: src/generation.c
	$(CC) $(CFLAGS) -o -g $@ $<

remove_gen:
	rm -f generation

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ_DIR)/*.o

.PHONY: all clean