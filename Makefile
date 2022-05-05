SRC_DIR = src
BUILD_DIR = build/debug
OBJ_NAME = exe

cc = gcc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(SRC_FILES:.c=.o)

INCLUDE_PATH = -Iinclude

LIB_PATH = -Llib -L/opt/homebrew/lib -lSDL2

COMPILER_FLAGS = -g -Wall -std=c99

LINKER_FLAGS = -lsdl2 -lsdl2_image

all:
	$(cc) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIB_PATH) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

