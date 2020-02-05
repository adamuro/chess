#include "logic.hpp"

bool isDifferentColor (int Piece, int Color) {
	return (pieceColor(Piece) != Color) ? 1 : 0;
}

void changePlayerToMove (int *playerToMove) {
	(*playerToMove) *= -1;
}

int pieceColor (int Piece) {
	if(Piece >= 0 && Piece <= 5)
		return White;
	if(Piece >= 6 && Piece <= 11)
		return Black;
	return 0;
}

bool inSameColumn(int currentSquare, int destSquare) {
	return (!(abs(currentSquare - destSquare) % 8)) ? 1 : 0;
}

bool inSameFile(int currentSquare, int destSquare) {
	int distToLeftEdge = currentSquare % 8;
	int leftEdge = currentSquare - distToLeftEdge;
	int rightEdge = currentSquare - distToLeftEdge + 7;

	return (destSquare >= leftEdge && destSquare <= rightEdge) ? 1 : 0;
}

bool Move (int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	switch(Piece) {
		case WP:
		case BP:
			return pawnMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WR:
		case BR:
			return rookMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WN:
		case BN:
			return knightMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
	}
	return 0;
}
