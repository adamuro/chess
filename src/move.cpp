#include "move.hpp"

using namespace std;

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
		case WR:
		case BR:
			return isLegalMove(destSquare, rookMoves(Board, Game));
		case WN:
		case BN:
			return isLegalMove(destSquare, knightMoves(Board, Game));
			/*
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
	int takeLeftSquare = nextSquare - 1;
	int takeRightSquare = nextSquare + 1;
	int doubleMoveSquare = nextSquare - 8 * Color;

	int nextPiece = Board -> getPiece(nextSquare);
	int doubleMovePiece = Board -> getPiece(doubleMoveSquare);
	int takeLeftPiece = Board -> getPiece(takeLeftSquare);
	int takeRightPiece = Board -> getPiece(takeRightSquare);

	static int possibleMoves [5];
	int movesNumber = 0;

	if(nextPiece == NP && doubleMovePiece == NP) {
		if(isPawnStartingSquare(Color, currentSquare))
			if(Board -> checkMove(doubleMoveSquare))
				possibleMoves[++movesNumber] = doubleMoveSquare;
	}
	if(nextPiece == NP) {
		if(Board -> checkMove(nextSquare))
			possibleMoves[++movesNumber] = nextSquare;
	}
	if(isDifferentColor(takeLeftPiece, Color)) {
		if(Board -> checkMove(takeLeftSquare))
			possibleMoves[++movesNumber] = takeLeftSquare;
	}
	if(isDifferentColor(takeRightPiece, Color)) {
		if(Board -> checkMove(takeRightSquare))
			possibleMoves[++movesNumber] = takeRightSquare;
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

int* rookMoves (boardData *Board, gameData *Game) {
	int Rook = Board -> getMarkedPiece();
	int Color = pieceColor(Rook);

	int currentSquare = Board -> getMarkedSquare();
	int distToLeftEdge = currentSquare % 8;
	int leftEdge = currentSquare - distToLeftEdge;
	int rightEdge = currentSquare - distToLeftEdge + 7;

	pair <int, int> moveSub [2] = {{-1, leftEdge}, {-8, 0}};
	pair <int, int> moveAdd [2] = {{1, rightEdge}, {8, 63}};

	static int possibleMoves [5];
	int movesNumber = 0;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + get<0>(moveSub[i]) ; Square >= get<1>(moveSub[i]) ; Square += get<0>(moveSub[i])) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves[++movesNumber] = Square;
					break;
				}
			}
			else
				break;
		}
	}
	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + get<0>(moveAdd[i]) ; Square <= get<1>(moveAdd[i]) ; Square += get<0>(moveAdd[i])) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves[++movesNumber] = Square;
					break;
				}
			}
			else
				break;
		}
	}

	possibleMoves[0] = movesNumber;
	return possibleMoves;
}
/* FIX WEIRD MOVES WHEN NEXT TO EDGE OF THE BOARD ETC */
int* knightMoves (boardData *Board, gameData *Game) {
	int Knight = Board -> getMarkedPiece();	
	int Color = pieceColor(Knight);
	int Moves [8] = {6, -6, 10, -10, 15, -15, 17, -17};

	static int possibleMoves [5];
	int movesNumber = 0;

	for(int i = 0 ; i < 8 ; i++) {
		int Square = Board -> getMarkedSquare() + Moves[i];
		if(Square >= 0 && Square <= 63) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
		}
	}
	possibleMoves[0] = movesNumber;
	return possibleMoves;
}
/*
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