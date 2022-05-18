# ===========================================================================
# * This program is the implementation of Conway's Game of Life in C
# * This program uses the SDL2 library to display all the content and views
# *
# * Run the main program with "sh run.sh"
# * This command will auto compile the program using the Makefile, 
# * and run the program "./build/debug/exe"
# * 
# * Authorship:       Yuelin Xin
# * Affiliation:      School of Computing, University of Leeds
# * Organization:     MiracleFactory
# * Organization URL: https://www.miraclefactory.co/
# ===========================================================================

# ===========================================================================
# this shell is used to automatically run the newest program
# ===========================================================================


clear
make
./build/debug/exe resources/data/.config resources/data/data.txt
