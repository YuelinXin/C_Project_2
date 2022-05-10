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
* This file is the used to invoke the main thread of the program (UI thread),
* and to take user inputs
**/

// head files
// ======================================================================
#include "game.h"
#include "util.h"
// ======================================================================

// program parameters
// ======================================================================
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
// ======================================================================


int main( void )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf( stderr, "SDL could not be initialized, SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        printf( "SDL initialized\n" );

        // create window
        // ======================================================================
        SDL_Window *window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if ( window == NULL )
        {
            fprintf( stderr, "Window could not be created, SDL_Error: %s\n", SDL_GetError() );
            SDL_Quit();
            return 1;
        }

        // create renderer
        // ======================================================================
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer *rend = SDL_CreateRenderer( window, -1, render_flags );
        if ( !rend )
        {
            fprintf( stderr, "Error trying to create a renderer: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        // create surface
        // ======================================================================
        SDL_Surface *surface = IMG_Load( "resources/images/mf.png" );
        if ( !surface )
        {
            fprintf( stderr, "Error creating a surface: %s\n", SDL_GetError() );
            SDL_DestroyRenderer( rend );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        // create texture
        // ======================================================================
        SDL_Texture *texture = SDL_CreateTextureFromSurface( rend, surface );
        SDL_FreeSurface( surface );
        if ( !texture )
        {
            fprintf( stderr, "Error creating a texture: %s\n", SDL_GetError() );
            SDL_DestroyRenderer( rend );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        // clear the window
        // ======================================================================
        SDL_RenderClear( rend );

        // draw the image to the window
        // ======================================================================
        SDL_RenderCopy( rend, texture, NULL, NULL );
        SDL_RenderPresent( rend );

        // create event loop
        // ======================================================================
        SDL_Event eve;
        int quit = FALSE;
        while( !quit )
        {
            while ( SDL_PollEvent( &eve ) )
            {
                if ( eve.type == SDL_QUIT )
                {
                    quit = 1;
                }
                if ( eve.button.button == SDL_BUTTON_LEFT )
                {
                    printf("left\n");
                }
            }
        }

        // clean up resources before exiting
        // ======================================================================
        SDL_DestroyTexture( texture );
        SDL_DestroyRenderer ( rend );
        SDL_DestroyWindow( window );
        SDL_Quit();
        printf( "Program terminated\n" );
    }
    return 0;
}
