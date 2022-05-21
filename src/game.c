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
        fscanf( config, "rows,cols: (%d,%d)\ndelay: (%d)", &board->rows, &board->columns, &board->delay );
    }
    fclose( config );
    printf( "[!] Program parameter: rows: %d, cols: %d, delay: %d\n", board->rows, board->columns, board->delay );
    // Error checking on the configuraiton
    if ( board->rows < MIN_ROWS || board->columns < MIN_COLS )
    {
        fprintf( stderr, "[Err] Board size is too small\n" );
        return EXIT_FAILURE;
    }
    if ( board->rows > MAX_ROWS || board->columns > MAX_COLS )
    {
        fprintf( stderr, "[Err] Board size is too large\n" );
        return EXIT_FAILURE;
    }
    if ( board->delay < MIN_DELAY || board->delay > MAX_DELAY )
    {
        fprintf( stderr, "[Err] Delay is out of range\n" );
        return EXIT_FAILURE;
    }

    // Read data from data file
    int count = 0;
    FILE *data = fopen( data_file, "r" );
    if ( data == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    board->grid = ( int** )malloc( board->rows * sizeof( int* ) );
    while( !feof( data ) )
    {
        for ( int i = 0; i < board->rows; i++ )
        {
            board->grid[i] = ( int* )malloc( board->columns * sizeof( int ) );
            for( int j = 0; j < board->columns; j++ )
            {
                fscanf( data, "%d ", &board->grid[i][j] );
                count++;
            }
        }
    }
    if ( count != board->rows * board->columns )
    {
        fprintf( stderr, "[!] Your configuration has changed\n" );
        fclose( data );
        free( board->grid );
        return EXIT_FAILURE;
    }
    fclose( data );
    return EXIT_SUCCESS;
}

int init_board_by_user( Board *board, SDL_Window *window )
{
    // Initialize the board
    board->grid = ( int** )malloc( board->rows * sizeof( int* ) );
    for ( int i = 0; i < board->rows; i++ )
    {
        board->grid[i] = ( int* )malloc( board->columns * sizeof( int ) );
        for( int j = 0; j < board->columns; j++ )
        {
            board->grid[i][j] = 0;
        }
    }
    return EXIT_SUCCESS;
}

int init_view( Window *view, SDL_Window *window, Board *board )
{
    int window_height, window_width;
    SDL_GL_GetDrawableSize( window, &window_width, &window_height );
    view->cell_size = ( window_width > window_height ) ? window_height / board->rows : window_width / board->columns;
    view->height_in_cells = window_height / view->cell_size;
    view->width_in_cells = window_width / view->cell_size;
    view->window_height = window_height;
    view->window_width = window_width;
    view->movement_speed_in_cells = 3;
    view->min_movement_speed_in_pixels = view->movement_speed_in_cells * view->cell_size;
    const int BOARD_HEIGHT = view->window_height / 4;
    const int BOARD_WIDTH = view->window_width / 4;
    // The starting position of the camera
    view->camera_x = ( BOARD_WIDTH - view->width_in_cells ) / 2;
    view->camera_y = ( BOARD_HEIGHT - view->height_in_cells ) / 2;
    return EXIT_SUCCESS;
}

void draw_board( Board* b, Window *view, SDL_Renderer* renderer )
{
    Uint8 red, green, blue;
    SDL_Rect rectangle;
    rectangle.w = rectangle.h = view->cell_size;
    // Iterate over all cells in the view and draw them to the renderer
    int screenHeight, screenWidth;
    SDL_GetRendererOutputSize( renderer, &screenWidth, &screenHeight );
    for ( int i = 0; i < b->rows; i++ )
    {
        for ( int j = 0; j < b->columns; j++ )
        {
            red = b->grid[i][j] ? LIVING_CELL_R : DEAD_CELL_R;
            green = b->grid[i][j] ? LIVING_CELL_G : DEAD_CELL_G;
            blue = b->grid[i][j] ? LIVING_CELL_B : DEAD_CELL_B;
            SDL_SetRenderDrawColor( renderer, red, green, blue, 255 );
            rectangle.x = j * view->cell_size;
            rectangle.y = i * view->cell_size;
            SDL_RenderDrawRect( renderer, &rectangle );
        }
    }
    // Draw the renderer to the screen
    // SDL_RenderPresent( renderer );
}

inline int count_neighbors( Board *b, int row, int col )
{
    int count = 0;
    for ( int i = row -1 ; i <= row + 1; i++ )
    {
        for ( int j = col - 1; j <= col + 1; j++ )
        {
            if ( i == row && j == col )
                continue;
            if ( i < 0 || i >= b->rows || j < 0 || j >= b->columns )
                continue;
            if ( b->grid[i][j] )
                count++;
        }
    }
    return count;
}

int update_next_generation( Board *b )
{
    int count;
    // Create a temp board to store the data for the next generation
    Board *next_gen = ( Board* )malloc( sizeof( Board ) );
    next_gen->rows = b->rows;
    next_gen->columns = b->columns;
    // Allocate temporary memory for the temp grid
    next_gen->grid = ( int** )malloc( b->rows * sizeof( int* ) );
    for ( int i = 0; i < b->rows; i++ )
    {
        next_gen->grid[i] = ( int* )malloc( b->columns * sizeof( int ) );
        for ( int j = 0; j < b->columns; j++ )
        {
            count = count_neighbors( b, i, j );
            if ( b->grid[i][j] )
            {
                if ( count < 2 || count > 3 )
                    next_gen->grid[i][j] = 0;
                else
                    next_gen->grid[i][j] = 1;
            }
            else
            {
                if ( count == 3 )
                    next_gen->grid[i][j] = 1;
                else
                    next_gen->grid[i][j] = 0;
            }
        }
    }
    // Copy the next generation grid to the current grid
    // Do not use memcpy!
    for ( int i = 0; i < b->rows; i++ )
    {
        for ( int j = 0; j < b->columns; j++ )
        {
            b->grid[i][j] = next_gen->grid[i][j];
        }
    }
    // Clear the temporary memory
    free( next_gen );
    return EXIT_SUCCESS;
}

int clear_all_cells( Board *b )
{
    for ( int i = 0; i < b->rows; i++ )
    {
        for ( int j = 0; j < b->columns; j++ )
        {
            b->grid[i][j] = 0;
        }
    }
    return EXIT_SUCCESS;
}

int write_back_to_file( char *config_file, char *data_file, Board *board )
{
    // Write config file
    FILE *config = fopen( config_file, "w" );
    if ( config == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    fprintf( config, "rows,cols: (%d,%d)\ndelay: (%d)", board->rows, board->columns, board->delay );
    fclose( config );

    // Write data file
    FILE *data = fopen( data_file, "w" );
    if ( data == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    for ( int i = 0; i < board->rows; i++ )
    {
        for ( int j = 0; j < board->columns; j++ )
        {
            fprintf( data, "%d ", board->grid[i][j] );
        }
        fprintf( data, "\n" );
    }
    fclose( data );
    return EXIT_SUCCESS;
}
