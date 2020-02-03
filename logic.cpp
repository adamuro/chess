#include "logic.h"

bool isWhite(int Piece) {
	return (Piece >= 0 && Piece <= 5) ? 1 : 0;
}

bool isBlack(int Piece) {
	return (Piece >= 6 && Piece <= 11) ? 1 : 0;
}

bool Move(int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	switch(Piece) {
		case WP:
			if(destSquare - currentSquare == 16 && currentSquare < 16 &&
			piecesOnBoard[currentSquare + 8] == NP &&
			piecesOnBoard[destSquare] == NP) {
				piecesOnBoard[destSquare] = WP;
				return 1;
			}
			else
				return 0;
			if(destSquare - currentSquare == 8 &&
			piecesOnBoard[destSquare] == NP) {
				piecesOnBoard[destSquare] = WP;
				return 1;
			}
			else
				return 0;
			if(destSquare - currentSquare == 7 ||
			destSquare - currentSquare == 9 && isBlack(destSquare)) {
				piecesOnBoard[destSquare] = WP;
				return 1;
			}
			else
				return 0;
	}
}