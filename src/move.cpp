#include "move.hpp"

bool pawnMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Pawn = (Color == White) ? WP : BP;
	if(currentSquare - destSquare == 16 * Color  &&
		piecesOnBoard[currentSquare - 8 * Color] == NP &&
		piecesOnBoard[destSquare] == NP) {
		if(Color == White && currentSquare >= 48) {
			piecesOnBoard[destSquare] = Pawn;
			piecesOnBoard[currentSquare] = NP;
			return 1;
		}
		if(Color == Black && currentSquare <= 16) {
			piecesOnBoard[destSquare] = Pawn;
			piecesOnBoard[currentSquare] = NP;
			return 1;
		}		
	}
	else if(currentSquare - destSquare == 8 * Color &&
		piecesOnBoard[destSquare] == NP) {
		piecesOnBoard[destSquare] = Pawn;
		piecesOnBoard[currentSquare] = NP;
		return 1;
	}
	else if(currentSquare - destSquare == 7 * Color || currentSquare - destSquare == 9 * Color) {
		if(isDifferentColor(piecesOnBoard[destSquare], Color)) {
			piecesOnBoard[destSquare] = Pawn;
			piecesOnBoard[currentSquare] = NP;
			return 1;
		}
	}
	return 0;
}

bool 