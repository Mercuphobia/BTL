PRO_DIR := .
OUTPUT_DIR := $(PRO_DIR)/output
SRC_DIR := $(PRO_DIR)/src
CC := /home/testserver/buildroot-2015.05/output/host/usr/bin/mips-buildroot-linux-uclibc-gcc
#C := gcc

LIB_DIR := $(PRO_DIR)/include
BIN := $(PRO_DIR)/bin

CFLAGS := -g
LDFLAGS := -lm


SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)
# $(warning $(OBJ_FILES))


all: $(OBJ_FILES) | $(BIN) $(OUTPUT_DIR)
	$(CC) $(OBJ_FILES) -o $(BIN)/app $(LDFLAGS)

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ -I$(LIB_DIR)

$(BIN):
	mkdir -p $(BIN)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OUTPUT_DIR)/*
	rm -f $(BIN)/*
