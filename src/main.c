/**
* @file: main.c
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
* This file is the used to invoke the main thread of the program (UI thread),
* and to take user inputs
**/

/** Head files **/
#include "game.h"
#include "util.h"

/** Program parameters **/
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;


int main( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf( stderr, "SDL could not be initialized, SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        printf( "SDL initialized\n" );

        // Create window
        SDL_Window *window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if ( window == NULL )
        {
            fprintf( stderr, "Window could not be created, SDL_Error: %s\n", SDL_GetError() );
            SDL_Quit();
            return EXIT_FAILURE;
        }

        // Create renderer
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer *rend = SDL_CreateRenderer( window, -1, render_flags );
        if ( !rend )
        {
            fprintf( stderr, "Error trying to create a renderer: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return EXIT_FAILURE;
        }

        // // Create surface
        // SDL_Surface *surface = IMG_Load( "resources/images/mf.png" );
        // if ( !surface )
        // {
        //     fprintf( stderr, "Error creating a surface: %s\n", SDL_GetError() );
        //     SDL_DestroyRenderer( rend );
        //     SDL_DestroyWindow( window );
        //     SDL_Quit();
        //     return EXIT_FAILURE;
        // }

        // // Create texture
        // SDL_Texture *texture = SDL_CreateTextureFromSurface( rend, surface );
        // SDL_FreeSurface( surface );
        // if ( !texture )
        // {
        //     fprintf( stderr, "Error creating a texture: %s\n", SDL_GetError() );
        //     SDL_DestroyRenderer( rend );
        //     SDL_DestroyWindow( window );
        //     SDL_Quit();
        //     return EXIT_FAILURE;
        // }

        // // Clear the window
        // SDL_RenderClear( rend );

        // // Draw the image to the window
        // SDL_RenderCopy( rend, texture, NULL, NULL );
        // SDL_RenderPresent( rend );

        // Initialize the board
        Board *board;
        board = malloc( sizeof( Board ) );
        init_board_from_file( "resources/data/.config", "resources/data/data.txt", board );

        // Initialize the view window
        Window view;
        init_view( &view, window, board );
        SDL_RenderClear( rend );
        draw_board( board, &view, rend );

        // Create event loop
        SDL_Event eve;
        int quit = FALSE;
        int pause = FALSE;
        while( !quit )
        {
            while ( SDL_PollEvent( &eve ) )
            {
                if ( eve.type == SDL_QUIT )
                {
                    write_back_to_file( "resources/data/.config", "resources/data/data.txt", board );
                    quit = TRUE;
                }
                else if ( eve.button.button == SDL_BUTTON_LEFT )
                {
                    printf( "left\n" );
                }
                else if ( eve.type == SDL_KEYDOWN )
                {
                    switch ( eve.key.keysym.scancode )
                    {
                        case SDL_SCANCODE_SPACE:
                            pause = !pause;
                            break;
                        case SDL_SCANCODE_Q:
                            write_back_to_file( "resources/data/.config", "resources/data/data.txt", board );
                            quit = TRUE;
                            break;
                        case SDL_SCANCODE_UP:
                            board->delay -= 20;
                            break;
                        case SDL_SCANCODE_DOWN:
                            board->delay += 20;
                            break;
                        default:
                            break;
                    }
                }
            }
            if ( !pause )
            {
                update_next_generation( board );
                SDL_RenderClear( rend );
                draw_board( board, &view, rend );
                SDL_Delay( board->delay ); // Change this into a better practice that does not block the main thread
            }
        }

        // Free the allocted memory
        free( board );

        // Clean SDL resources before exiting
        // SDL_DestroyTexture( texture );
        SDL_DestroyRenderer ( rend );
        SDL_DestroyWindow( window );
        SDL_Quit();
        printf( "Program terminated\n" );
    }
    return EXIT_SUCCESS;
}
