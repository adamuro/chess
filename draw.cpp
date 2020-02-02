#include "draw.h"

void drawBoard (RenderWindow *Window, RectangleShape *Board) {
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			Window -> draw(Board[i * 8 + j]);
}

void drawPieces (RenderWindow *Window, string *piecesOnBoard) {
	Sprite WhitePawn;
	Texture WhitePawnTexture;
	WhitePawnTexture.loadFromFile("./images/WhitePawn.png");

	WhitePawn.setTexture(WhitePawnTexture);

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			if(!piecesOnBoard[i + j * 8].compare("WP")) {
				WhitePawn.setPosition(i * 80, j * 80);
				Window -> draw(WhitePawn);
			}
		}
	}
}