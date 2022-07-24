/**
* @file: util.h
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
* This file contains all the utility function prototypes
* This file also contains all the functional marcos
**/


#ifndef UTIL_H
#define UTIL_H


/** Define all the functional marcos **/
#define FALSE 0
#define TRUE 1
#define File_IO_Err "[Err] File could not be accessed, check:\n-> Does file exist?\n-> Directory/file name correct?\n-> Is file corrupted?\n"


/** Declare all the function prototypes **/
/* Read binary files to the int buffer 
    *
    * @param filename: the name of the file to be read
    * @param buffer: the buffer to store the data
    * @param rows: the number of rows in the file
    * @param cols: the number of columns in the file
    *
    * @return: EXIT_SUCCESS if the file is read successfully, EXIT_FAILURE otherwise
*/
int read_bin( char *filename, unsigned int *buffer, int rows, int cols );

/* Write binary files from the int buffer 
    *
    * @param filename: the name of the file to be written
    * @param buffer: the buffer to store the data
    * @param rows: the number of rows in the file
    * @param cols: the number of columns in the file
    *
    * @return: EXIT_SUCCESS if the file is written successfully, EXIT_FAILURE otherwise
*/
int write_bin( char *filename, unsigned int *buffer, int rows, int cols );

/* Render text onto the screen
    *
    * @param rend: the renderer to render the text
    * @param smooth_operator: the font of the text
    * @param color: the SDL color of the text
    * @param text: the pointer to the text to be rendered
    * @param x: the x coordinate of the text
    * @param y: the y coordinate of the text
    *
    * @return: EXIT_SUCCESS if the text is rendered successfully
*/
int render_text( SDL_Renderer *rend, TTF_Font* smooth_operator, SDL_Color color, char *text, int x, int y );

/* Render text onto the screen
    *
    * @param rend: the renderer to render the text
    * @param file: the image file to be rendered
    * @param x: the x coordinate of the text
    * @param y: the y coordinate of the text
    *
    * @return: EXIT_SUCCESS if the text is rendered successfully
*/
int render_button( SDL_Renderer *rend, const char *file, int x, int y );

/* Get the number input from the user
    *
    * @return: The inputed number if the number is read successfully, -1 otherwise
*/
int number_input( void );

#endif
