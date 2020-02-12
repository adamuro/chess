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
		case WRL:
		case WRR:
		case BRL:
		case BRR:
			return isLegalMove(destSquare, rookMoves(Board, Game));
		case WN:
		case BN:
			return isLegalMove(destSquare, knightMoves(Board, Game));
		case WB:
		case BB:
			return isLegalMove(destSquare, bishopMoves(Board, Game));
		case WK:
		case BK:
			return isLegalMove(destSquare, kingMoves(Board, Game));
			/*
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

	static int possibleMoves [16];
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
	int currentSquare = Board -> getMarkedSquare();
	int horizontalMoves [2] = {6, -10};
	int verticalMoves [2] = {15, -17};

	static int possibleMoves [8];
	int movesNumber = 0;

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - horizontalMoves[i];
		if(Square >= 0 && Square <= 63 && currentSquare % 8 < 6) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + horizontalMoves[i];
		if(Square >= 0 && Square <= 63 && currentSquare % 8 > 1) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - verticalMoves[i];
		if(Square >= 0 && Square <= 63 && currentSquare % 8 < 7) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + verticalMoves[i];
		if(Square >= 0 && Square <= 63 && currentSquare % 8 > 0) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves[++movesNumber] = Square;
		}
	}

	possibleMoves[0] = movesNumber;
	return possibleMoves;
}

int* bishopMoves (boardData *Board, gameData *Game) {
	int Bishop = Board -> getMarkedPiece();
	int Color = pieceColor(Bishop);
	int currentSquare = Board -> getMarkedSquare();
	
	int moveLeft [2] = {7, -9};
	int moveRight [2] = {-7, 9};

	static int possibleMoves [16];
	int movesNumber = 0;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + moveLeft[i] ; Square >= 0 && Square <= 63 && Square % 8 >= 0 && Square % 8 < 7 ; Square += moveLeft[i]) {
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
		for(int Square = currentSquare + moveRight[i] ; Square >= 0 && Square <= 63 && Square % 8 <= 7 && Square % 8 > 0 ; Square += moveRight[i]) {
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

int* kingMoves (boardData *Board, gameData *Game) {
	int King = Board -> getMarkedPiece();
	int Color = pieceColor(King);
	int currentSquare = Board -> getMarkedSquare();

	int allyRookLeft = (pieceColor(King) == White) ? WRL : BRL;
	int allyRookRight = (pieceColor(King) == White) ? WRR : BRR;
	
	int Moves [8] = {1, -1, 7, -7, 8, -8, 9, -9};

	static int possibleMoves [12];
	int movesNumber = 0;

	for(int i = 0 ; i < 8 ; i++) {
		int Square = currentSquare + Moves[i];
		if(Square >= 0 && Square <= 63 && Board -> getPiece(Square) == NP) {
			if(Board -> checkMove(Square))
				possibleMoves[++movesNumber] = Square;
		}
		else if(isDifferentColor(Board -> getPiece(Square), Color)) {
			if(Board -> checkMove(Square))
				possibleMoves[++movesNumber] = Square;
		}
	}
	if(!(Game -> wasPieceMoved(King) || Game -> wasPieceMoved(allyRookLeft))) {
		if(!Board -> inCheck(Color)) {
			if(!(Board -> isSquareAttacked(currentSquare - 1, Color) || Board -> isSquareAttacked(currentSquare - 2, Color))) {
				if(Board -> getPiece(currentSquare - 1) == NP && Board -> getPiece(currentSquare - 2) == NP && Board -> getPiece(currentSquare - 3) == NP) {
					possibleMoves[++movesNumber] = currentSquare - 2;
					possibleMoves[++movesNumber] = currentSquare - 3;
					possibleMoves[++movesNumber] = currentSquare - 4;
				}
			}
		}
	}

	if(!(Game -> wasPieceMoved(King) || Game -> wasPieceMoved(allyRookRight))) {
		if(!Board -> inCheck(Color)) {
			if(!(Board -> isSquareAttacked(currentSquare + 1, Color) || Board -> isSquareAttacked(currentSquare + 2, Color))) {
				if(Board -> getPiece(currentSquare + 1) == NP && Board -> getPiece(currentSquare + 2) == NP) {
					possibleMoves[++movesNumber] = currentSquare + 2;
					possibleMoves[++movesNumber] = currentSquare + 3;
				}
			}
		}
	}

	possibleMoves[0] = movesNumber;
	return possibleMoves;
}
/*
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