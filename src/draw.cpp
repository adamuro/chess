#include "draw.hpp"

void drawBoard (RenderWindow *Window, RectangleShape *Board) {
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			Window -> draw(Board[i * 8 + j]);
}

void drawPieces (RenderWindow *Window, Texture *piecesTextures, int *piecesOnBoard) {
	Sprite Piece;
	int squareEdge = windowHeight / 8;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int currentPiece = piecesOnBoard[j * 8 + i];
			if(currentPiece != NP) {
				Piece.setTexture(piecesTextures[currentPiece]);
				Piece.setPosition(i * squareEdge, j * squareEdge);
				Window -> draw(Piece);
			}
		}
	}
}