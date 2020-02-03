#include "logic.hpp"

bool isWhite(int Piece) {
	return (Piece >= 0 && Piece <= 5) ? 1 : 0;
}

bool isBlack(int Piece) {
	return (Piece >= 6 && Piece <= 11) ? 1 : 0;
}

bool Move(int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	switch(Piece) {
		case WP:
			if(currentSquare - destSquare == 16 && currentSquare > 48 &&
			piecesOnBoard[currentSquare - 8] == NP &&
			piecesOnBoard[destSquare] == NP) {
				piecesOnBoard[destSquare] = WP;
				piecesOnBoard[currentSquare] = NP;
				return 1;
			}
			else if(currentSquare - destSquare == 8 &&
			piecesOnBoard[destSquare] == NP) {
				piecesOnBoard[destSquare] = WP;
				piecesOnBoard[currentSquare] = NP;
				return 1;
			}
			else if((currentSquare - destSquare == 7 || currentSquare - destSquare == 9) &&
			isBlack(piecesOnBoard[destSquare])) {
				piecesOnBoard[destSquare] = WP;
				piecesOnBoard[currentSquare] = NP;
				return 1;
			}
			return 0;
	}
	return 0;
}