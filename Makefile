CC = g++
CFLAGS = -Wall -Werror
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ =\
	./src/main.cpp \
	./src/logic.cpp \
	./src/move.cpp \
	./src/user.cpp \
	./src/board.cpp \
	./src/game.cpp \
	./src/menu.cpp

all: main

clean:
		rm -f *.o chess

.cpp.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o chess