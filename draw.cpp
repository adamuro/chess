#include "draw.h"

void drawBoard (RenderWindow *Window, RectangleShape *Board) {
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			Window -> draw(Board[i * 8 + j]);
}

void drawPieces (RenderWindow *Window, Texture *piecesTextures, int *piecesOnBoard) {
	Sprite Piece;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int currentPiece = piecesOnBoard[j * 8 + i];
			if(currentPiece != NP) {
				Piece.setTexture(piecesTextures[currentPiece]);
				Piece.setPosition(i * 80, j * 80);
				Window -> draw(Piece);
			}

		}
	}
}