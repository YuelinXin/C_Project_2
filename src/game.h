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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


/** Define all the marcos in the game **/
#define LIVING_CELL_R 125   // The red channel of the living cell
#define LIVING_CELL_G 81   // The green channel of the living cell
#define LIVING_CELL_B 227   // The blue channel of the living cell
#define DEAD_CELL_R 240      // The red channel of the dead cell
#define DEAD_CELL_G 240      // The green channel of the dead cell
#define DEAD_CELL_B 240      // The blue channel of the dead cell
#define BACKGROUND_R 245      // The red channel of the background
#define BACKGROUND_G 245      // The green channel of the background
#define BACKGROUND_B 245      // The blue channel of the background
#define MIN_ROWS 15         // The minimum rows of the board
#define MIN_COLS 30         // The minimum columns of the board
#define MAX_ROWS 45       // The maximum number of rows in the board
#define MAX_COLS 80       // The maximum number of columns in the board
#define MIN_DELAY 20        // The minimum delay between two frames
#define MAX_DELAY 1000      // The maximum delay between two frames


/** define all the structs used in the board **/
typedef struct
{
    int rows;        // The number of rows in the board
    int columns;     // The number of columns in the board
    int delay;       // The delay between two frames
    int **grid;      // The grid of the board
} Board;

typedef struct
{
    int camera_x;                       // The x coordinate of the camera
    int camera_y;                       // The y coordinate of the camera
    int cell_size;                      // The size of each cell
    int height_in_cells;                // The height of the board in cells
    int width_in_cells;                 // The width of the board in cells
    int window_height;                  // The height of the SDL_Window
    int window_width;                   // The width of the SDL_Window
    int movement_speed_in_cells;        // The speed of the camera movement
    int min_movement_speed_in_pixels;   // The minimum speed of the camera movement
} Window;


/** Declare all the function prototypes **/
/* Initialize the board with the given configuration file and data file 
    *
    * @param config_file: the name of the configuration file
    * @param data_file: the name of the data file
    * @param board: the board to be initialized
    *
    * @return: EXIT_SUCCESS if the board is initialized successfully, EXIT_FAILURE otherwise
*/
int init_board_from_file( char *config_file, char *data_file, Board *board );

/* Initialize the baord by user
    *
    * @param board: the board to be initialized
    *
    * @return: EXIT_SUCCESS if the board is initialized successfully, EXIT_FAILURE otherwise
*/
int init_board_by_user( Board *board );

/* Initialize the view according to the SDL_Window 
    *
    * @param view: the view to be initialized
    * @param board: the board that is initialized previously
    *
    * @return: EXIT_SUCCESS if the view is initialized successfully
*/
int init_view( Window *view, Board *board );

/* Draw the board on the window
    *
    * @param board: the board to be drawn
    * @param window: the window configuration
    * @param renderer: the renderer to draw the board
    *
    * @return: none
*/
void draw_board( Board* board, Window *player_view, SDL_Renderer* renderer );

/* Count the number of neighbors of a given cell
    *
    * @param board: the board used in the game
    * @param row: the row number of the given cell
    * @param board: the column number of the given cell
    *
    * @return: EXIT_SUCCESS if the count is performed successfully
*/
int count_neighbors( Board *board, int row, int col );

/* Update the board according to the rules of the game, this function holds the logic behind Conway's Game of Life
    *
    * @param board: the board to be updated
    *
    * @return: EXIT_SUCCESS if the board is updated successfully
*/
int update_next_generation( Board *board );

/* Clear all the cells in the board
    *
    * @param board: the board to be cleared
    *
    * @return: EXIT_SUCCESS if the board is cleared successfully
*/
int clear_all_cells( Board *board );

/* Initialize the board with the given configuration file and data file 
    *
    * @param config_file: the name of the configuration file
    * @param data_file: the name of the data file
    * @param board: the board to be initialized
    *
    * @return: EXIT_SUCCESS if the file is saved successfully, EXIT_FAILURE otherwise
*/
int write_back_to_file( char *config_file, char *data_file, Board *board );


#endif
