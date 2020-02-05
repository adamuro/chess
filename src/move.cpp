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
	/* If players wants to take, check if there is anything to take */
	else if(currentSquare - destSquare == 7 * Color || currentSquare - destSquare == 9 * Color) {
		if(isDifferentColor(piecesOnBoard[destSquare], Color)) {
			piecesOnBoard[destSquare] = Pawn;
			piecesOnBoard[currentSquare] = NP;
			return 1;
		}
	}
	return 0;
}

bool rookMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Rook = (Color == White) ? WR : BR;
	int Direction;

	if(inSameColumn(currentSquare, destSquare))					// If the rook is in the same column as it's destination,
		Direction = (destSquare - currentSquare > 0) ? 8 : -8;	// it will move vertically(+8 for up, -8 for down).
	else if(inSameFile(currentSquare, destSquare))				// And if they are on the same file,
		Direction = (destSquare - currentSquare > 0) ? 1 : -1;	// it will move horizontally(+1 for right, -1 for left).
	else														// If neither of those conditions are true,
		return 0;												// the rook can't be moved.
	
	for(int i = currentSquare + Direction ; i != destSquare ; i += Direction) {
		if(piecesOnBoard[i] != NP)	// If any square between the rook and its destination is occupied by other piece,
			return 0;				// the rook can't move.
	}
	
	if(piecesOnBoard[destSquare] == NP || isDifferentColor(piecesOnBoard[destSquare], Color)) {
		piecesOnBoard[destSquare] = Rook;	// If the destination sqare is empty or an opponent's piece occupies it.
		piecesOnBoard[currentSquare] = NP;	// Move the rook.
		return 1;
	}
	return 0;
}

bool knightMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Knight = (Color == White) ? WN : BN;
	int squareDifference = abs(destSquare - currentSquare);
	if(piecesOnBoard[destSquare] == NP || isDifferentColor(piecesOnBoard[destSquare], Color)) {
	  	if(squareDifference == 17 ||			// If clicked square is empty
		   squareDifference == 15 ||			// or opposite color piece occupies it
		   squareDifference == 10 ||			// and it's a legal knight move,
		   squareDifference == 6) {				// move the knight.
		   	piecesOnBoard[destSquare] = Knight;
		    piecesOnBoard[currentSquare] = NP;
	    	return 1;
		}
	}
	return 0;
}

bool bishopMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Bishop = (Color == White) ? WB : BB;
	int squareDifference = destSquare - currentSquare;
	int Direction;

	if(!(abs(squareDifference) % 7))				 // If the bishop is asked
		Direction = (squareDifference > 0) ? 7 : -7; // to move diagonally
	else if(!(abs(squareDifference) % 9))			 // set the direction it will move.
		Direction = (squareDifference > 0) ? 9 : -9; // Otherwise return false.
	else
		return 0;
	
	for(int i = currentSquare + Direction ; i != destSquare ; i += Direction) {
		if(piecesOnBoard[i] != NP)	// If any square between the bishop and its destination
			return 0;				// is occupied by other piece, return false.
	}

	if(piecesOnBoard[destSquare] == NP || isDifferentColor(piecesOnBoard[destSquare], Color)) {
		piecesOnBoard[destSquare] = Bishop;	// If the clicked square is empty
		piecesOnBoard[currentSquare] = NP;	// or occupied by opposite color piece,
		return 1;							// move the bishop/
	}										// In other case return false.
	return 0;
}

bool kingMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int King = (Color == White) ? WK : BK;
	int squareDifference = abs(destSquare - currentSquare);

	if(piecesOnBoard[destSquare] == NP || isDifferentColor(piecesOnBoard[destSquare], Color)) {
		if(squareDifference == 1 ||				// If the king is asked to move
		   squareDifference == 7 ||				// in any direction
		   squareDifference == 8 ||				// by just one square,
		   squareDifference == 9) {				// move the king.
		   	piecesOnBoard[destSquare] = King;	// In other case return false.
		   	piecesOnBoard[currentSquare] = NP;
		   	return 1;
		}
	}
	return 0;
}

bool queenMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Queen = (Color == White) ? WQ : BQ;
	/* If the queen is asked to move like a bishop or a rook, move the queen. */
	if(rookMove(Color, currentSquare, destSquare, piecesOnBoard) ||
	   bishopMove(Color, currentSquare, destSquare, piecesOnBoard)) {
		piecesOnBoard[destSquare] = Queen;
		return 1;
	}
	return 0;
}