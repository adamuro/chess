#include "draw.h"

void drawBoard (RenderWindow *Window, RectangleShape *Board) {
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			Window -> draw(Board[i * 8 + j]);
}

void drawPieces (RenderWindow *Window, int *piecesOnBoard) {
	Texture WhitePawn;
	WhitePawn.loadFromFile("./images/WhitePawn.png");

	Texture WhiteRook;
	WhiteRook.loadFromFile("./images/WhiteRook.png");

	Texture WhiteBishop;
	WhiteBishop.loadFromFile("./images/WhiteBishop.png");

	Texture WhiteKnight;
	WhiteKnight.loadFromFile("./images/WhiteKnight.png");

	Sprite Piece;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			switch(piecesOnBoard[j * 8 + i]) {
				case NP:
					break;
				case WP:
					Piece.setTexture(WhitePawn);
					break;
				case WR:
					Piece.setTexture(WhiteRook);
					break;
				case WK:
					Piece.setTexture(WhiteKnight);
					break;
				case WB:
					Piece.setTexture(WhiteBishop);
					break;

			}
			if(piecesOnBoard[j * 8 + i] != NP) {
				Piece.setPosition(i * 80, j * 80);
				Window -> draw(Piece);
			}

		}
	}
}