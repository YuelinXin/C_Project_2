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


int init_board_from_file( char *config_file, char *data_file, Board *board )
{
    // Read rows and cols from config file
    FILE *config = fopen( config_file, "r" );
    if ( config == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    while( !feof( config ) )
    {
        fscanf( config, "rows,cols: %d,%d", &board->rows, &board->columns );
    }
    fclose( config );
    printf( "rows: %d, cols: %d\n", board->rows, board->columns );

    // Read data from data file
    board->grid = (int**)malloc( board->rows * sizeof( int* ) );
    FILE *data = fopen( data_file, "r" );
    if ( data == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    while( !feof( data ) )
    {
        for ( int i = 0; i < board->rows; i++ )
        {
            board->grid[i] = (int*)malloc( board->columns * sizeof( int ) );
            for( int j = 0; j < board->columns; j++ )
            {
                fscanf( data, "%d ", &board->grid[i][j] );
                printf( "%d ", board->grid[i][j] );
            }
            printf( "\n" );
        }
    }
    fclose( data );
    return EXIT_SUCCESS;
}

void draw_board( Board* b, Window *player_view, SDL_Renderer* renderer )
{
    Uint8 red, green, blue, current_cell_alive;
    SDL_Rect rectangle;
    rectangle.w = rectangle.h = player_view->cell_size;

    // Iterate over all cells in the view and draw them to the renderer
    int screenHeight, screenWidth;
    SDL_GetRendererOutputSize( renderer, &screenWidth, &screenHeight );
    for ( int i = 0; i < b->rows; i++ )
    {
        for ( int j = 0; j < b->columns; j++ )
        {
            current_cell_alive = b->grid[i][j];

            red = current_cell_alive ? LIVING_CELL_R : DEAD_CELL_R;
            green = current_cell_alive ? LIVING_CELL_G : DEAD_CELL_G;
            blue = current_cell_alive ? LIVING_CELL_B : DEAD_CELL_B;

            SDL_SetRenderDrawColor( renderer, red, green, blue, 255 );
            rectangle.x = j*player_view->cell_size;
            rectangle.y = i*player_view->cell_size;
            SDL_RenderDrawRect( renderer, &rectangle );
        }
    }
    // Draw the renderer to the screen
    SDL_RenderPresent( renderer );
}
