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
/*
void draw (RenderWindow *window, RectangleShape Board string *piecesOnBoard) {
	Sprite WhitePawn;
	Texture WhitePawnTexture;
	WhitePawnTexture.loadFromFile("./images/WhitePawn.png");

	WhitePawn.setTexture(WhitePawnTexture);

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			window->draw(Board[i * 8 + j]);
			if(!piecesOnBoard[i + j * 8].compare("WP")) {
				WhitePawn.setPosition(i * 80, j * 80);
				window->draw(WhitePawn);
			}
		}
	}
}
*/
// POINTER TO WINDOW DOESNT WORK //
// TRIED SF::THREAD, MIGHT WORK  //