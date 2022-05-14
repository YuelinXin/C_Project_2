/**
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
* This file contains all the utility functions used in the program
* All the according function prototypes are defined in util.h
**/

/** Head files **/
#include "game.h"
#include "util.h"


int read_bin( char *filename, unsigned int *buffer, int rows, int cols )
{
    // Open binary file
    FILE *fp = fopen( filename, "rb" );
    if ( fp == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    buffer = malloc( rows * cols * sizeof( unsigned char ) );
    fread( buffer, sizeof( buffer ), 1, fp );
    for ( int i = 0; i < 10; i++ )
    {
        printf( "%d ", buffer[i] );
    }
    fclose( fp );
    return EXIT_SUCCESS;
}

int write_bin( char *filename, unsigned int *buffer, int rows, int cols )
{
    // Open binary file
    FILE *fp = fopen( filename, "wb" );
    if ( fp == NULL )
    {
        fprintf( stderr, File_IO_Err );
        return EXIT_FAILURE;
    }
    fwrite( buffer, sizeof( buffer ), 1, fp );
    fclose( fp );
    return EXIT_SUCCESS;
}
