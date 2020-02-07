#include "move.hpp"

void moveBoardUpdate (int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	piecesOnBoard[destSquare] = Piece;
	piecesOnBoard[currentSquare] = NP;
}

bool isMoveLegal (int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	int takenPiece = piecesOnBoard[destSquare];
	
	moveBoardUpdate(Piece, currentSquare, destSquare, piecesOnBoard);
	
	if(isInCheck(pieceColor(Piece), piecesOnBoard)) {
		moveBoardUpdate(Piece, destSquare, currentSquare, piecesOnBoard);
		piecesOnBoard[destSquare] = takenPiece;
		return 0;
	}
	return 1;
}

bool Move (int Piece, int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame) {
	switch(Piece) {
		case WP:
		case BP:
			return pawnMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard, currentGame);
		case WR:
		case BR:
			return rookMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WN:
		case BN:
			return knightMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WB:
		case BB:
			return bishopMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WK:
		case BK:
			return kingMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard, currentGame);
		case WQ:
		case BQ:
			return queenMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
	}
	return 0;
}

/* Need to implement these functions using Piece and pieceColor(Piece) instead of Color */
bool pawnMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame) {
	int Pawn = piecesOnBoard[currentSquare];
	int destPiece = piecesOnBoard[destSquare];
	int nextSquare = currentSquare - 8 * Color;
	int nextPiece = piecesOnBoard[nextSquare];
	int Distance = (currentSquare - destSquare) * Color;
	int enPassantSquare = destSquare + 8 * Color;
	int enPassantPiece = piecesOnBoard[enPassantSquare];

	if(Distance == 16 && destPiece == NP && nextPiece == NP) {
		if(isPawnStartingSquare(Color, currentSquare)) { 
			return isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard);
		}
	}
	else if(Distance == 8 && destPiece == NP) {
		return isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard);
	}
	/* If players wants to take, check if there is anything to take */
	else if(Distance == 7 || Distance == 9) {
		if(isDifferentColor(destPiece, Color))
			return isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard);
		if(isDifferentColorPawn(Color, enPassantPiece)) {
			if(currentGame -> movedLast(enPassantPiece)) {
				if(isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard)) {
					piecesOnBoard[enPassantSquare] = NP;
					return 1;
				}
			}
		}
	}
	return 0;
}

bool rookMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Rook = piecesOnBoard[currentSquare];
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
		return isMoveLegal(Rook, currentSquare, destSquare, piecesOnBoard);
	}
	return 0;
}

bool knightMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Knight = piecesOnBoard[currentSquare];
	int squareDifference = abs(destSquare - currentSquare);
	
	if(piecesOnBoard[destSquare] == NP || isDifferentColor(piecesOnBoard[destSquare], Color)) {
	  	if(squareDifference == 17 ||	// If clicked square is empty
		   squareDifference == 15 ||	// or opposite color piece occupies it
		   squareDifference == 10 ||	// and it's a legal knight move,
		   squareDifference == 6) {		// move the knight.
		   	return isMoveLegal(Knight, currentSquare, destSquare, piecesOnBoard);
		}
	}
	return 0;
}

bool bishopMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Bishop = piecesOnBoard[currentSquare];
	int squareDifference = destSquare - currentSquare;
	int destPiece = piecesOnBoard[destSquare];
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

	if(destPiece == NP || isDifferentColor(destPiece, Color)) {
		return isMoveLegal(Bishop, currentSquare, destSquare, piecesOnBoard);							// move the bishop/
	}
	return 0;
}

bool kingMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame) {
	int King = piecesOnBoard[currentSquare];
	int AllyRook = (pieceColor(King) == White) ? WR : BR;
	int destPiece = piecesOnBoard[destSquare];
	int squareDifference = abs(destSquare - currentSquare);

	if(destPiece == NP || isDifferentColor(destPiece, Color)) {
		if(squareDifference == 1 ||				// If the king is asked to move
		   squareDifference == 7 ||				// in any direction
		   squareDifference == 8 ||				// by just one square,
		   squareDifference == 9) {				// move the king.
		   	return isMoveLegal(King, currentSquare, destSquare, piecesOnBoard);
		}
	}
	if(destPiece == AllyRook) {
		if(!currentGame -> wasPieceMoved(King) && !currentGame -> wasPieceMoved(AllyRook)) {
			int Direction = (destSquare - currentSquare > 0) ? 1 : -1;

			if(isAttacked(currentSquare, Color, piecesOnBoard))
				return 0;
			for(int i = currentSquare + Direction ; i != destSquare ; i += Direction) {
				if(piecesOnBoard[i] != NP || isAttacked(i, Color, piecesOnBoard))
					return 0;
			}
			moveBoardUpdate(King, currentSquare, currentSquare + Direction * 2, piecesOnBoard);
			moveBoardUpdate(AllyRook, destSquare, currentSquare + Direction, piecesOnBoard);
			return 1;
		}
	}
	return 0;
}

bool queenMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard) {
	int Queen = piecesOnBoard[currentSquare];
	/* If the queen is asked to move like a bishop or a rook, move the queen. */
	if(rookMove(Color, currentSquare, destSquare, piecesOnBoard) ||
	   bishopMove(Color, currentSquare, destSquare, piecesOnBoard)) {
		if(isMoveLegal(Queen, currentSquare, destSquare, piecesOnBoard))
			return 1;
	}
	return 0;
}