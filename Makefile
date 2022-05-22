# ===========================================================================
# * This program is the implementation of Conway's Game of Life in C
# * This program uses the SDL2 library to display all the content and views
# *
# * Run the main program with "sh run.sh"
# * This command will auto compile the program using the Makefile, 
# * and run the program "./build/debug/exe"
# * 
# * Authorship:       Yuelin Xin
# * Affiliation:      School of Computing, University of Leeds
# * Organization:     MiracleFactory
# * Organization URL: https://www.miraclefactory.co/
# ===========================================================================

# ===========================================================================
# This Makefile is used to automatically compile the program
# ===========================================================================

# ===========================================================================
# Link the libraries with: ln -s <origin_path> <destination_path>
# ===========================================================================

SRC_DIR = src
BUILD_DIR = build/debug
OBJ_NAME = GameOfLife
cc = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_PATH = -Iinclude
LIB_PATH = -Llib -L/opt/homebrew/lib
COMPILER_FLAGS = -g -Wall -std=c99
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all:
	$(cc) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIB_PATH) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

clean:
	rm -f $(BUILD_DIR)/$(OBJ_NAME)
