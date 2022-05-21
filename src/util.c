/**
* @file: util.c
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

int render_text( SDL_Renderer *rend, TTF_Font* smooth_operator, SDL_Color color, char *text, int x, int y )
{
    SDL_Surface *surface_smooth_operator = TTF_RenderText_Blended( smooth_operator, text, color );
    SDL_Texture* Message = SDL_CreateTextureFromSurface( rend, surface_smooth_operator );
    int w, h;
    SDL_QueryTexture( Message, NULL, NULL, &w, &h );
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(rend, Message, NULL, &rect);
    SDL_FreeSurface( surface_smooth_operator );
    SDL_DestroyTexture( Message );
    return EXIT_SUCCESS;
}

int render_button( SDL_Renderer *rend, const char *file, int x, int y )
{
    SDL_Surface *surface_button = IMG_Load( file );
    SDL_Texture* Button = SDL_CreateTextureFromSurface( rend, surface_button );
    SDL_Rect rect = {x, y, 24, 24};
    SDL_RenderCopy(rend, Button, NULL, &rect);
    SDL_FreeSurface( surface_button );
    SDL_DestroyTexture( Button );
    return EXIT_SUCCESS;
}
