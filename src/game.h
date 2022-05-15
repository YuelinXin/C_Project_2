/**
* @file: game.h
* 
* This program is the implementation of Conway's Game of Life in C
* This program uses the SDL2 library to display all the content and views
*
* Run the main program with "sh run.sh"
* This command will auto compile the program using the Makefile, 
* and run the program "./build/debug/exe"
* 
* Authorship:       Yuelin Xin
* Affiliation:      School of Computing, University of Leeds
* Organization:     MiracleFactory
* Organization URL: https://www.miraclefactory.co/
**/

/**
* This file contains all the function prototypes that are used to implement Conway's Game of Life
* This file also contains all the marcos related to the game
**/


#ifndef BOARD_H
#define BOARD_H


/** Include all the libraries **/
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


/** Define all the marcos in the game **/
#define LIVING_CELL_R 255
#define LIVING_CELL_G 255
#define LIVING_CELL_B 255
#define DEAD_CELL_R 20
#define DEAD_CELL_G 20
#define DEAD_CELL_B 20
#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MIN_DELAY 25
#define MAX_DELAY 2000


/** define all the structs used in the board **/
typedef struct
{
    int rows;
    int columns;
    int **grid;
} Board;

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
} Window;


/** Define all the function prototypes **/
/* Initialize the board with the given configuration file and data file 
    *
    * @param config_file: the name of the configuration file
    * @param data_file: the name of the data file
    * @param board: the board to be initialized
    *
    * @return: EXIT_SUCCESS if the board is initialized successfully, EXIT_FAILURE otherwise
*/
int init_board_from_file( char *config_file, char *data_file, Board *board );

int init_view( Window *view, SDL_Window *window, Board *board );

/* Draw the board on the window
    *
    * @param board: the board to be drawn
    * @param window: the window configuration
    * @param renderer: the renderer to draw the board
    *
    * @return: none
*/
void draw_board( Board* b, Window *player_view, SDL_Renderer* renderer );

int count_neighbors( Board *b, int row, int col );

int update_next_generation( Board *b );


#endif
