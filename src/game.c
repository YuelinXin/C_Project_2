/**
* @file: game.c
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
* This file contains all the functions that implement the logic behind Conway's Game of Life
* This file also contains all the rendering functions of the game
* All the according function prototypes are defined in game.h
**/

/** Head files **/
#include "game.h"
#include "util.h"


Board* init_board( int rows, int columns, int living_cell_count )
{
    Board* board = calloc( 1, board_size( rows, columns ) );
    board->rows = rows;
    board->columns = columns;
    unsigned int *buffer;
    read_file( "./src/data/data.bin", , rows, columns );
    for ( int i = 0; i < living_cell_count; i++ )
    {
        rand_x = random_uniform( columns );
        rand_y = random_uniform( rows );
        // Skip cells that are already alive
        if ( cell_state( rand_x, rand_y, board ) )
        {
            i--;
            continue;
        }
        change_cell_state( rand_x, rand_y, TRUE, board );
    }
    return board;
}

// Calculate the memory size of the board
inline int board_size( int rows, int columns )
{
    int size = sizeof( Board ) + ( rows * columns ) / 8;
    size += ( rows * columns % 8 ) ? 1 : 0;
    return size;
}

// int random_uniform( int n )
// {
//     int rand_val;
//     do
//     {
//         rand_val = random();
//     }
//     while ( rand_val >= INT_MAX - ( INT_MAX % n ) );
//     return rand_val % n ;
// }

inline Uint8 cell_state( int x, int y, Board* b )
{
    if ( !pos_in_board( x, y, b ) )
    {
        return FALSE;
    }
    int bitmask = cell_bitmask( x, y, b);
    int cell_states = b->grid[ ( ( y*b->columns + x ) / 8 ) ];
    return ( cell_states & bitmask ) != 0;
}

inline Uint8 change_cell_state( int x, int y, bool state, Board *b )
{
    if ( !pos_in_board( x, y, b ) )
    {
        return FALSE;
    }
    int bitmask = cell_bitmask( x, y, b );
    if ( state )
    {
        return b->grid[ ( y*b->columns + x ) / 8 ] |= bitmask;
    }
    return b->grid[ ( y*b->columns + x ) / 8 ] &= ~bitmask;
}

inline int cell_bitmask( int x, int y, Board *b )
{
    return ( int ) powf( 2, ( y*b->columns + x ) % 8 );
}

void draw_board( Board* board, Window *player_view, SDL_Renderer* renderer )
{
    Uint8 red, green, blue;
    Uint8 current_cell_alive;
    SDL_Rect rectangle;
    rectangle.w = rectangle.h = player_view->cell_size;

    // Iterate over all cells in the view and draw them to the renderer
    int screenHeight, screenWidth;
    SDL_GetRendererOutputSize( renderer, &screenWidth, &screenHeight );
    for ( int row = 0; row < player_view->height_in_cells; row++ )
    {
        for ( int column = 0; column < player_view->width_in_cells; column++ )
        {
            current_cell_alive = cell_state( column + player_view->camera_x, row + player_view->camera_y, board );

            red = current_cell_alive ? LIVING_CELL_R : DEAD_CELL_R;
            green = current_cell_alive ? LIVING_CELL_G : DEAD_CELL_G;
            blue = current_cell_alive ? LIVING_CELL_B : DEAD_CELL_B;

            SDL_SetRenderDrawColor( renderer, red, green, blue, 255 );
            rectangle.x = column*player_view->cell_size;
            rectangle.y = row*player_view->cell_size;
            SDL_RenderDrawRect( renderer, &rectangle );
        }
    }
    // Draw the renderer to the screen
    SDL_RenderPresent( renderer );
}
