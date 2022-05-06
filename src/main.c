// ======================================================================
// run the main program with ```sh run.sh```
// this command will auto compile the program using Makefile, 
// and run the program ./build/debug/exe
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// program parameters
// ======================================================================
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
// ======================================================================


int main( void )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        printf( "SDL initialized!\n" );

        // create window
        // ======================================================================
        SDL_Window *window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if ( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            SDL_Quit();
            return 1;
        }

        // create renderer
        // ======================================================================
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer *rend = SDL_CreateRenderer( window, -1, render_flags );
        if ( !rend )
        {
            printf( "error trying to create a renderer: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        // create surface
        // ======================================================================
        SDL_Surface *surface = IMG_Load( "resources/mf.png" );
        if ( !surface )
        {
            printf( "error creating a surface: %s\n", SDL_GetError() );
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
            printf( "error creating a texture: %s\n", SDL_GetError() );
            SDL_DestroyRenderer( rend );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        // clear the window
        SDL_RenderClear( rend );

        // draw the image to the window
        SDL_RenderCopy( rend, texture, NULL, NULL );
        SDL_RenderPresent( rend );

        SDL_Event eve;
        int quit = 0;
        while( !quit )
        {
            while ( SDL_PollEvent( &eve ) )
            {
                if ( eve.type == SDL_QUIT )
                {
                    quit = 1;
                }
            }
        }

        // wait a few seconds
        // SDL_Delay( 5000 );

        // clean up resources before exiting
        SDL_DestroyTexture( texture );
        SDL_DestroyRenderer ( rend );

        SDL_DestroyWindow( window );
        SDL_Quit();
        printf( "Program terminated" );
    }
    // SDL_Quit();
    return 0;
}
