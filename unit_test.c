/**
* @file: unit_test.c
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
* This file contains all the functions used in unit test
**/

/** Head files **/
#include <stdio.h>
#include <string.h>
#include "include/CUnit/Basic.h"
#include "src/game.h"
#include "src/util.h"
#include "unit_test.h"



/** All the tested functions are here **/
// Test function 1: clear_all_cells
int clear_all_cells( Board *b )
{
    if ( b == NULL )
        return EXIT_FAILURE;
    for ( int i = 0; i < b->rows; i++ )
    {
        for ( int j = 0; j < b->columns; j++ )
        {
            b->grid[i][j] = 0;
        }
    }
    return EXIT_SUCCESS;
}

// Test function 2: init_view
int init_view( Window *view, Board *board )
{
    if ( view == NULL || board == NULL )
        return EXIT_FAILURE;
    view->cell_size = 17;
    view->window_height = ( view->cell_size * board->rows ) + 40;
    view->window_width = view->cell_size * board->columns;
    view->height_in_cells = view->window_height / view->cell_size;
    view->width_in_cells = view->window_width / view->cell_size;
    view->movement_speed_in_cells = 3;
    view->min_movement_speed_in_pixels = view->movement_speed_in_cells * view->cell_size;
    const int BOARD_HEIGHT = view->window_height / 4;
    const int BOARD_WIDTH = view->window_width / 4;
    view->camera_x = ( BOARD_WIDTH - view->width_in_cells ) / 2;
    view->camera_y = ( BOARD_HEIGHT - view->height_in_cells ) / 2;
    return EXIT_SUCCESS;
}

// Test function 3: count_neighbors
inline int count_neighbors( Board *b, int row, int col )
{
    if ( b == NULL )
        return EXIT_FAILURE;
    if ( row < 0 || row >= b->rows || col < 0 || col >= b->columns )
        return EXIT_FAILURE;
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

// Test function 4: write_back_to_file
int write_back_to_file( char *config_file, char *data_file, Board *board )
{
    // Write config file
    FILE *config = fopen( config_file, "w" );
    if ( config == NULL )
    {
        return EXIT_FAILURE;
    }
    fprintf( config, "rows,cols: (%d,%d)\ndelay: (%d)", board->rows, board->columns, board->delay );
    fclose( config );

    // Write data file
    FILE *data = fopen( data_file, "w" );
    if ( data == NULL )
    {
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

// Test 5: init_board_by_user
int init_board_by_user( Board *board )
{
    if ( board == NULL )
        return EXIT_FAILURE;
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

// Test function 6: init_board_from_file
int init_board_from_file( char *config_file, char *data_file, Board *board )
{
    // Read rows and cols from config file
    FILE *config = fopen( config_file, "r" );
    if ( config == NULL )
    {
        return EXIT_FAILURE;
    }
    while( !feof( config ) )
    {
        fscanf( config, "rows,cols: (%d,%d)\ndelay: (%d)", &board->rows, &board->columns, &board->delay );
    }
    fclose( config );
    // Error checking on the configuraiton
    if ( board->rows < MIN_ROWS || board->columns < MIN_COLS )
    {
        return EXIT_FAILURE;
    }
    if ( board->rows > MAX_ROWS || board->columns > MAX_COLS )
    {
        return EXIT_FAILURE;
    }
    if ( board->delay < MIN_DELAY || board->delay > MAX_DELAY )
    {
        return EXIT_FAILURE;
    }

    // Read data from data file
    int count = 0;
    FILE *data = fopen( data_file, "r" );
    if ( data == NULL )
    {
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
        fclose( data );
        free( board->grid );
        return 2;
    }
    fclose( data );
    return EXIT_SUCCESS;
}


/** All the test cases here **/
// Test 1: clear_all_cells
static void test_clear_all_cells( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( clear_all_cells( NULL ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    Board *b = tool_create_board();
    CU_ASSERT_EQUAL( clear_all_cells( b ), EXIT_SUCCESS );
    free( b );
}

// Test 2: init_view
static void test_init_view( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( init_view( NULL, NULL ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    Board *b = tool_create_board();
    Window view;
    CU_ASSERT_EQUAL( init_view( &view, b ), EXIT_SUCCESS );
    free( b );
}

// Test 3: count_neighbors
static void test_count_neighbors( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( count_neighbors( NULL, 0, 0 ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    Board *b = tool_create_board();
    CU_ASSERT_EQUAL( count_neighbors( b, 0, 0 ), 3 );
    // Test case 3: row and col are normal
    CU_ASSERT_EQUAL( count_neighbors( b, 2, 2 ), 8 );
    // Test case 4: row and col are out of bound
    CU_ASSERT_EQUAL( count_neighbors( b, 12, 12 ), EXIT_FAILURE );
    free( b );
}

// Test 4: write_back_to_file
static void test_write_back_to_file( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( write_back_to_file( NULL, NULL, NULL ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    // Board *b = tool_create_board();
    // CU_ASSERT_EQUAL( write_back_to_file( "config.txt", "data.txt", b ), EXIT_SUCCESS );
    // free( b );
}

// Test 5: init_board_by_user
static void test_init_board_by_user( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( init_board_by_user( NULL ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    Board *b;
    b = malloc( sizeof( Board ) );
    b->columns = b->rows = 10;
    CU_ASSERT_EQUAL( init_board_by_user( b ), EXIT_SUCCESS );
    free( b );
}

// Test 6: init_board_from_file
static void test_init_board_from_file( void )
{
    // Test case 1: board is NULL
    CU_ASSERT_EQUAL( init_board_from_file( NULL, NULL, NULL ), EXIT_FAILURE );
    // Test case 2: board is not NULL
    Board *b = malloc( sizeof( Board ) );
    CU_ASSERT_EQUAL( init_board_from_file( "resources/data/.config", "resources/data/data.txt", b ), EXIT_SUCCESS );
    // Test case 3: config file is not found
    CU_ASSERT_EQUAL( init_board_from_file( "resources/data/config.txt", "resources/data/data.txt", b ), EXIT_FAILURE );
    // Test case 4: data file is not found
    CU_ASSERT_EQUAL( init_board_from_file( "resources/data/.config", "resources/data/test.txt", b ), EXIT_FAILURE );
    free( b );
}


/** Tool functions for the testing **/
// This is the tool function for creating a new board (for testing suites only!)
static Board *tool_create_board( void )
{
    Board *b = ( Board * )malloc( sizeof( Board ) );
    b->rows = 10;
    b->columns = 10;
    b->grid = ( int** )malloc( b->rows * sizeof( int* ) );
    for ( int i = 0; i < b->rows; i++ )
    {
        b->grid[i] = ( int* )malloc( b->columns * sizeof( int ) );
        for ( int j = 0; j < b->columns; j++ )
        {
            b->grid[i][j] = 1;
        }
    }
    return b;
}

static int suite_init( void )
{
    return 0;
}

static int suite_clean( void )
{
    return 0;
}

int main( void )
{
    CU_pSuite pSuite = NULL;

    // Initialize the CUnit test registry
    if ( CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }

    // Add a suite to the registry
    pSuite = CU_add_suite( "suite_clear_all_cells", suite_init, suite_clean );
    if ( NULL == pSuite )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // Add the tests to the suite
    if ( ( NULL == CU_add_test( pSuite, "test_clear_all_cells", test_clear_all_cells ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ( ( NULL == CU_add_test( pSuite, "test_init_view", test_init_view ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ( ( NULL == CU_add_test( pSuite, "test_count_neighbors", test_count_neighbors ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ( ( NULL == CU_add_test( pSuite, "test_write_back_to_file", test_write_back_to_file ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ( ( NULL == CU_add_test( pSuite, "test_init_board_by_user", test_init_board_by_user ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ( ( NULL == CU_add_test( pSuite, "test_init_board_from_file", test_init_board_from_file ) ) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode( CU_BRM_VERBOSE );
    CU_basic_run_tests();

    // Clean up registry and return
    CU_cleanup_registry();
    return CU_get_error();
}
