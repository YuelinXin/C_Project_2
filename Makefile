
# code details

EXE = ./exe
SRC= main.c
LIBS = -I/library/Frameworks/SDL2.framework/Headers/SDL

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:      main.c
# library.o:   library.c library.h admin.h user.h utility.h book_management.h
# admin.o: 	 admin.c admin.h book_management.h
# user.o:      user.c user.h book_management.h
# utility.o:   utility.c utility.h 
