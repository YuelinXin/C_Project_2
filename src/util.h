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
#define File_IO_Err "File could not be accessed, check:\n-> Does file exist?\n-> Directory/file name correct?\n-> Is file corrupted?\n"


/** Define all the function prototypes **/
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


#endif
