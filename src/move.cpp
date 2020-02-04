#include "move.hpp"

bool pawnMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Pawn = (Color == White) ? WP : BP;				  // Check pawn color.
	if(currentSquare - destSquare == 16 * Color  &&		  // If player wants to
		piecesOnBoard[currentSquare - 8 * Color] == NP && // move two sqares forward,
		piecesOnBoard[destSquare] == NP) {				  // check if both sqares are empty
		if(Color == White && currentSquare >= 48) {		  // and if the pawn
			piecesOnBoard[destSquare] = Pawn;			  // is at the starting position.
			piecesOnBoard[currentSquare] = NP;			  // If all is true,
			return 1;									  // move the pawn.
		}												  /* That was for white pawn. */
		if(Color == Black && currentSquare <= 16) {		  // Check if black pawn
			piecesOnBoard[destSquare] = Pawn;			  // is at its starting position.
			piecesOnBoard[currentSquare] = NP;			  /* And that was for black pawn. */
			return 1;
		}		
	}
	else if(currentSquare - destSquare == 8 * Color &&	  // If player wants to move
		piecesOnBoard[destSquare] == NP) {				  // one square forward,
		piecesOnBoard[destSquare] = Pawn;				  // check if the square is empty
		piecesOnBoard[currentSquare] = NP;				  // and move it if it was empty.
		return 1;
	}
	/* If players wants to take, check if there's anything to take */
	else if(currentSquare - destSquare == 7 * Color || currentSquare - destSquare == 9 * Color) {
		if(isDifferentColor(piecesOnBoard[destSquare], Color)) {
			piecesOnBoard[destSquare] = Pawn;
			piecesOnBoard[currentSquare] = NP;
			return 1;
		}
	}
	return 0;
}