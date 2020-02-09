#include "move.hpp"

bool checkAfterMove (int destSquare, boardData *Board) {
	Board -> checkMove(destSquare);
	if(isInCheck(Board -> getMarkedPieceColor(), Board -> getPiecesOnBoard())) {
		Board -> checkDone(destSquare);
		return 1;
	}
	Board -> checkDone(destSquare);
	return 0;
}

bool isLegalMove (int destSquare, int *possibleMoves) {
	for(int i = 1 ; i <= possibleMoves[0] ; i++) {
		if(possibleMoves[i] == destSquare)
			return 1;
	}
	return 0;
}

bool Move (boardData *Board, gameData *Game) {
	int Piece = Board -> getMarkedPiece();
	int destSquare = Board -> getClickedSquare();

	switch(Piece) {
		case WP:
		case BP:
			return isLegalMove(destSquare, pawnMoves(Board, Game));

			/*
		case WR:
		case BR:
			return rookMove(currentSquare, destSquare, piecesOnBoard);
		case WN:
		case BN:
			return knightMove(currentSquare, destSquare, piecesOnBoard);
		case WB:
		case BB:
			return bishopMove(currentSquare, destSquare, piecesOnBoard);
		case WK:
		case BK:
			return kingMove(currentSquare, destSquare, piecesOnBoard, Game);
		case WQ:
		case BQ:
			return queenMove(currentSquare, destSquare, piecesOnBoard);*/
	}
	return 0;
}

/* Need to implement these functions using Piece and pieceColor(Piece) instead of Color */
int* pawnMoves (boardData *Board, gameData *Game) {
	int Pawn = Board -> getMarkedPiece();
	int Color = pieceColor(Pawn);

	int currentSquare = Board -> getMarkedSquare();
	int nextSquare = currentSquare - 8 * Color;
	int doubleMoveSquare = nextSquare - 8 * Color;

	int nextPiece = Board -> getPiece(nextSquare);
	int doubleMovePiece = Board -> getPiece(doubleMoveSquare);

	static int possibleMoves [5];
	int movesNumber = 0;

	if(nextPiece == NP && doubleMovePiece == NP) {
		if(isPawnStartingSquare(Color, currentSquare))
			if(!checkAfterMove(doubleMoveSquare, Board))
				possibleMoves[++movesNumber] = doubleMoveSquare;
	}
	if(nextPiece == NP) {
		if(!checkAfterMove(nextSquare, Board))
			possibleMoves[++movesNumber] = nextSquare;
	}
	/*
	else if(Distance == 7 || Distance == 9) {
		if(isDifferentColor(destPiece, Color))
			return isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard);
		if(isDifferentColorPawn(Color, enPassantPiece)) {
			if(Game -> movedLast(enPassantPiece)) {
				if(isMoveLegal(Pawn, currentSquare, destSquare, piecesOnBoard)) {
					piecesOnBoard[enPassantSquare] = NP;
					return 1;
				}
			}
		}
	}*/
	possibleMoves[0] = movesNumber;
	return possibleMoves;
}
/*
bool rookMove (int currentSquare, int destSquare, int *piecesOnBoard) {
	int Rook = piecesOnBoard[currentSquare];
	int Color = pieceColor(Rook);
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

bool knightMove (int currentSquare, int destSquare, int *piecesOnBoard) {
	int Knight = piecesOnBoard[currentSquare];
	int Color = pieceColor(Knight);
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

bool bishopMove (int currentSquare, int destSquare, int *piecesOnBoard) {
	int Bishop = piecesOnBoard[currentSquare];
	int Color = pieceColor(Bishop);
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

bool kingMove (int currentSquare, int destSquare, int *piecesOnBoard, gameData *Game) {
	int King = piecesOnBoard[currentSquare];
	int Color = pieceColor(King);
	int allyRook = (pieceColor(King) == White) ? WR : BR;
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
	if(destPiece == allyRook) {
		if(!Game -> wasPieceMoved(King) && !Game -> wasPieceMoved(allyRook)) {
			int Direction = (destSquare - currentSquare > 0) ? 1 : -1;

			if(isAttacked(currentSquare, Color, piecesOnBoard))
				return 0;
			for(int i = currentSquare + Direction ; i != destSquare ; i += Direction) {
				if(piecesOnBoard[i] != NP || isAttacked(i, Color, piecesOnBoard))
					return 0;
			}
			moveBoardUpdate(King, currentSquare, currentSquare + Direction * 2, piecesOnBoard);
			moveBoardUpdate(allyRook, destSquare, currentSquare + Direction, piecesOnBoard);
			return 1;
		}
	}
	return 0;
}

bool queenMove (int currentSquare, int destSquare, int *piecesOnBoard) {
	int Queen = piecesOnBoard[currentSquare];

	if(rookMove(currentSquare, destSquare, piecesOnBoard) ||
	   bishopMove(currentSquare, destSquare, piecesOnBoard)) {
		if(isMoveLegal(Queen, currentSquare, destSquare, piecesOnBoard))
			return 1;
	}
	return 0;
}
*/