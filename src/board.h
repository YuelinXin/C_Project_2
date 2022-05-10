#ifndef BOARD_H
#define BOARD_H


// include all the libraries
// ======================================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <stdint.h>
// #include <ctype.h>
// #include <time.h>
// #include <math.h>
// #include <assert.h>

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
// ======================================================================


// define all the marcos
// ======================================================================
#define FALSE 0
#define TRUE 1
#define LIVING_CELL_R 255
#define LIVING_CELL_G 255
#define LIVING_CELL_B 255
#define DEAD_CELL_R 20
#define DEAD_CELL_G 20
#define DEAD_CELL_B 20
// ======================================================================


// define all the structs used in the board
// ======================================================================
typedef struct
{
    int rows;
    int columns;
    Uint8 grid[ 0 ];
} board;

typedef struct
{
    int camera_x;
    int camera_y;
    int cell_size;
    int height_in_cells;
    int width_in_cells;
    int window_height;
    int window_width;
    int movement_speed_in_cells;
    int min_movement_speed_in_pixels;
} view;
// ======================================================================






#endif