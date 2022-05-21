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
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 680;


int main( int argc, char** argv )
{
    // Read command line arguments
    if ( argc != 3 )
    {
        printf( "Usage: ./build/debug/exe <config_file> <data_file>\n" );
        return EXIT_FAILURE;
    }
    char *config_file = malloc( strlen( argv[1] ) + 1 );
    char *data_file = malloc( strlen( argv[2] ) + 1 );
    strcpy( config_file, argv[1] );
    strcpy( data_file, argv[2] );

    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf( stderr, "[Err] SDL could not be initialized, SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        printf( "[OK] SDL initialized\n" );

        // Create window
        SDL_Window *window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if ( window == NULL )
        {
            fprintf( stderr, "[Err] Window could not be created, SDL_Error: %s\n", SDL_GetError() );
            SDL_Quit();
            return EXIT_FAILURE;
        }
        SDL_SetWindowIcon( window, IMG_Load( "resources/images/game_of_life.png" ) );

        // Create renderer
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer *rend = SDL_CreateRenderer( window, -1, render_flags );
        if ( !rend )
        {
            fprintf( stderr, "[Err] Error trying to create a renderer: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return EXIT_FAILURE;
        }

        // Create font rend
        if ( TTF_Init() == -1 )
        {
            fprintf( stderr, "[Err] Error trying to initialize TTF: %s\n", SDL_GetError() );
            SDL_DestroyRenderer( rend );
            SDL_DestroyWindow( window );
            SDL_Quit();
            return EXIT_FAILURE;
        }
        TTF_Font* smooth_operator = TTF_OpenFont( "resources/fonts/Formula1-Regular.ttf", 16 );
        SDL_Color Gray = {80, 80, 80, 255};

        // Initialize the board
        Board *board;
        board = malloc( sizeof( Board ) );
        if ( init_board_from_file( config_file, data_file, board ) )
        {
            init_board_by_user( board, window );
        }

        // Initialize the view window
        Window view;
        init_view( &view, window, board );

        // Create event loop
        SDL_Event eve;
        int quit = FALSE;
        int pause = TRUE;           // Always pause the game at the beginning
        int last_update_tick = 0;   // The tick of the last update, used to control the update frequency
        int x, y;                   // The position of the mouse
        int interation = 0;         // The number of iterations
        char *str = malloc( sizeof( char ) * 50 );      // The iteration string
        char *str_1 = malloc( sizeof( char ) * 50 );    // The delay string
        while ( !quit )
        {
            // Do some string works here
            sprintf( str, "Iteration - %d", interation );
            sprintf( str_1, "Delay - %d", board->delay );
            // Listen to events
            while ( SDL_PollEvent( &eve ) )
            {
                // Kill the main thread if the close button is clicked
                if ( eve.type == SDL_QUIT )
                {
                    write_back_to_file( config_file, data_file, board );
                    quit = TRUE;
                }
                // Mouse functionalities
                else if ( eve.button.button == SDL_BUTTON_LEFT || eve.button.button == SDL_BUTTON_RIGHT )
                {
                    x = eve.button.x / ( view.cell_size );
                    y = eve.button.y / ( view.cell_size );
                    // The mouse clicks on the board
                    if ( x >= 0 && x < board->columns && y >= 0 && y < board->rows )
                    {
                        pause = TRUE;
                        if ( eve.button.button == SDL_BUTTON_LEFT)  // Add new living cells
                            board->grid[y][x] = 1;
                        else if ( eve.button.button == SDL_BUTTON_RIGHT )   // Remove living cells
                            board->grid[y][x] = 0;
                        // Remember to rerender everything on the screen if something is changed
                        SDL_RenderClear( rend );
                        draw_board( board, &view, rend );
                        render_text( rend, smooth_operator, Gray, str, 15, 650 );
                        render_text( rend, smooth_operator, Gray, str_1, 180, 650 );
                        SDL_RenderPresent( rend );
                    }
                    // The mouse clicks on the play button
                    else if ( eve.type == SDL_MOUSEBUTTONDOWN && eve.button.x >= view.window_width - 40 && 
                        eve.button.x <= view.window_width - 16 && eve.button.y >= view.window_height - 32 && 
                        eve.button.y <= view.window_height - 8 )
                    {
                        pause = !pause;
                    }
                }
                // Keyboard functionalities
                else if ( eve.type == SDL_KEYDOWN )
                {
                    switch ( eve.key.keysym.scancode )
                    {
                        case SDL_SCANCODE_SPACE:
                            pause = !pause;
                            break;
                        case SDL_SCANCODE_C:
                            pause = TRUE;
                            clear_all_cells( board );
                            // Remember to rerender everything on the screen if something is changed
                            SDL_RenderClear( rend );
                            draw_board( board, &view, rend );
                            render_text( rend, smooth_operator, Gray, str, 15, 650 );
                            render_text( rend, smooth_operator, Gray, str_1, 180, 650 );
                            SDL_RenderPresent( rend );
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            write_back_to_file( config_file, data_file, board );
                            quit = TRUE;
                            break;
                        case SDL_SCANCODE_UP:
                            if ( board->delay - 20 >= MIN_DELAY )
                                board->delay -= 20;
                            break;
                        case SDL_SCANCODE_DOWN:
                            if ( board->delay + 20 <= MAX_DELAY )
                                board->delay += 20;
                            break;
                        default:
                            break;
                    }
                }
            }
            // Update the board if the game is not paused, control the frequency of updates
            if ( !pause && !( ( SDL_GetTicks( ) - last_update_tick ) < board->delay ) )
            {
                update_next_generation( board );
                // Update the current tick to the last update tick
                last_update_tick = SDL_GetTicks();
                interation++;
            }
            // Do the drawing and rendering
            SDL_SetRenderDrawColor( rend, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255 );
            SDL_RenderClear( rend );
            draw_board( board, &view, rend );
            render_text( rend, smooth_operator, Gray, str, 15, 650 );
            render_text( rend, smooth_operator, Gray, str_1, 180, 650 );
            if ( pause )
            {
                SDL_SetWindowTitle( window, "Conway's Game of Life - Paused" );
                render_button( rend, "resources/images/play.svg", view.window_width - 40, view.window_height - 32 );
            }
            else
            {
                SDL_SetWindowTitle( window, "Conway's Game of Life" );
                render_button( rend, "resources/images/pause.svg", view.window_width - 40, view.window_height - 32 );
            }
            SDL_RenderPresent( rend );
        }

        // Free the allocated memory
        free( board );
        free( config_file );
        free( data_file );
        free( str );
        free( str_1 );

        // Clean SDL resources before exiting
        SDL_DestroyRenderer ( rend );
        SDL_DestroyWindow( window );
        SDL_Quit();
        printf( "[!] Program terminated\n" );
    }
    return EXIT_SUCCESS;
}
