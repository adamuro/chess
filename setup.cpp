#include "setup.h"

void boardSetup (RectangleShape *Board) {
	int squareEdge = WindowHeight / 8;
	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int squareNum = i * 8 + j;
			Board[squareNum].setSize(Vector2f(squareEdge, squareEdge));
			Board[squareNum].setPosition(squareEdge * i, squareEdge * j);
			if((squareNum + i) % 2)	
				Board[squareNum].setFillColor(Color(White));
			else
				Board[squareNum].setFillColor(Color(Black));
		}
	}
}