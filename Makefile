PRO_DIR := .
OUTPUT_DIR := $(PRO_DIR)/output
SRC_DIR := $(PRO_DIR)/src
#CC := /home/testserver/buildroot-2015.05/output/host/usr/bin/mips-buildroot-linux-uclibc-gcc
CC := gcc
LIB_DIR := $(PRO_DIR)/include
BIN := $(PRO_DIR)/bin

#cach2
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)
 
build: $(OBJ_FILES) | $(BIN) $(OUTPUT_DIR)
	$(CC) $(OBJ_FILES) -o $(BIN)/app

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ -I$(LIB_DIR)

$(BIN):
	mkdir -p $(BIN)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OUTPUT_DIR)/*
	rm -f $(BIN)/*

#
# cach1:
# build: main.o hello.o
# #	$(CC) output/main.o output/hello.o -o $(BIN)/app
# 	$(CC) $(OUTPUT_PATH)/*.o -o $(BIN)/app

# main.o: src/main.c 
# 	$(CC) -c src/main.c -o output/main.o -I$(LIB_DIR)

# hello.o: src/hello.c
# 	$(CC) -c src/hello.c -o output/hello.o -I$(LIB_DIR)

# clean:
# 	rm -f output/*
