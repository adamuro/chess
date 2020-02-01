CC = g++
CFLAGS = -Wall -Werror
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ =\
	main.cpp \
	setup.cpp

all: main

clean:
		rm -f *.o chess

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o chess