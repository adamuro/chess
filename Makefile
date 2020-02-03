CC = g++
CFLAGS = -Wall -Werror
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ =\
	./src/main.cpp \
	./src/setup.cpp \
	./src/logic.cpp \
	./src/draw.cpp \
	./src/user.cpp

all: main

clean:
		rm -f *.o chess

.cpp.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o chess