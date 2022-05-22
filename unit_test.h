/**
* @file: unit_test.h
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
* This file contains all function prototypes used in unit test
**/


#ifndef UNIT_TEST_H
#define UNIT_TEST_H


/** Define all the function prototypes **/
/* The tool function for creating a board
    *
    * @return: a pointer to the created board
    * 
*/
static Board *tool_create_board( void );


#endif