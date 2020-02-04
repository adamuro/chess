#include "logic.hpp"

bool isDifferentColor (int Piece, int Color) {
	if(Color == White)
		return (Piece >= 0 && Piece <= 5) ? 0 : 1;
	return (Piece >= 0 && Piece <= 5) ? 1 : 0;
}

void changePlayerToMove (int *playerToMove) {
	(*playerToMove) *= -1;
}

int pieceColor (int Piece) {
	return (Piece >= 0 && Piece <= 5) ? 1 : -1;
}

bool Move (int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	switch(Piece) {
		case WP:
		case BP:
			return pawnMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		
	}
	return 0;
}