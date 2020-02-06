#include "logic.hpp"

bool isDifferentColor (int Piece, int Color) {
	return (pieceColor(Piece) != Color && pieceColor(Piece)) ? 1 : 0;
}

bool isSameColor (int Piece, int Color) {
	return (pieceColor(Piece) == Color) ? 1 : 0;
}

void changePlayerToMove (int *playerToMove) {
	(*playerToMove) *= -1;
}

int pieceColor (int Piece) {
	if(Piece >= 0 && Piece <= 5)
		return White;
	if(Piece >= 6 && Piece <= 11)
		return Black;
	return 0;
}

bool inSameColumn (int currentSquare, int destSquare) {
	return (!(abs(currentSquare - destSquare) % 8)) ? 1 : 0;
}

bool inSameFile (int currentSquare, int destSquare) {
	int distToLeftEdge = currentSquare % 8;
	int leftEdge = currentSquare - distToLeftEdge;
	int rightEdge = currentSquare - distToLeftEdge + 7;

	return (destSquare >= leftEdge && destSquare <= rightEdge) ? 1 : 0;
}

bool isDifferentColorQueen (int Color, int Piece) {
	if(Color == White && Piece == BQ)
		return 1;
	if(Color == Black && Piece == WQ)
		return 1;
	return 0;
}

bool isDifferentColorRook (int Color, int Piece) {
	if(Color == White && Piece == BR)
		return 1;
	if(Color == Black && Piece == WR)
		return 1;
	return 0;
}

bool isDifferentColorBishop (int Color, int Piece) {
	if(Color == White && Piece == BB)
		return 1;
	if(Color == Black && Piece == WB)
		return 1;
	return 0;
}

bool isDifferentColorKnight (int Color, int Piece) {
	if(Color == White && Piece == BN)
		return 1;
	if(Color == Black && Piece == WN)
		return 1;
	return 0;
}

bool isDifferentColorPawn (int Color, int Piece) {
	if(Color == White && Piece == BP)
		return 1;
	if(Color == Black && Piece == WP)
		return 1;
	return 0;
}

bool isInCheck (int Color, int *piecesOnBoard) {
	int King = (Color == White) ? WK : BK;
	int kingSquare;

	for(int i = 0 ; i < 64 ; i++) {
		if(piecesOnBoard[i] == King) {
			kingSquare = i;
			break;
		}
	}

	int distToLeftEdge = kingSquare % 8;
	int leftEdge = kingSquare - distToLeftEdge;
	int rightEdge = kingSquare - distToLeftEdge + 7;

	int Diagonal[4] = {7, -7, 9, -9};
	int knightAttack[8] = {6, -6, 10, -10, 15, -15, 17, -17};
	int pawnAttack[2] = {7 * Color, 9 * Color};
	/* Searching for vertical and horizontal attacks on the king (queen or rook) */
	/* From the left */
	for(int i = kingSquare - 1 ; i >= leftEdge ; i--) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDifferentColorBishop(Color, Piece) || isDifferentColorKnight(Color, Piece) || isDifferentColorPawn(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From the right */
	for(int i = kingSquare + 1 ; i <= rightEdge ; i++) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDifferentColorBishop(Color, Piece) || isDifferentColorKnight(Color, Piece) || isDifferentColorPawn(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From above */
	for(int i = kingSquare + 8 ; i < 64 ; i+= 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDifferentColorBishop(Color, Piece) || isDifferentColorKnight(Color, Piece) || isDifferentColorPawn(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From beneath */
	for(int i = kingSquare - 8 ; i >= 0 ; i-= 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDifferentColorBishop(Color, Piece) || isDifferentColorKnight(Color, Piece) || isDifferentColorPawn(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* Searching for diagonal attacks on the king (queen or bishop) */
	for(int i = 0 ; i < 4 ; i++) {
		for(int j = kingSquare + Diagonal[i] ; j >= 0 && j < 64 ; j += Diagonal[i]) {
			int Piece = piecesOnBoard[j];
			if(isSameColor(piecesOnBoard[j], Color))
				break;
			if(isDifferentColorRook(Color, Piece) || isDifferentColorKnight(Color, Piece) || isDifferentColorPawn(Color, Piece))
				break;
			if(isDifferentColorQueen(Color, Piece) || isDifferentColorBishop(Color, Piece))
				return 1;
		}
	}
	/* Searching for knights which attack the king */
	for(int i = 0 ; i < 8 ; i++) {
		int knightSquare = kingSquare + knightAttack[i];
		if(knightSquare >= 0 && knightSquare < 64)
			if(isDifferentColorKnight(Color, piecesOnBoard[knightSquare]))
				return 1;
	}
	/* Searching for pawns which attack the king */
	for(int i = 0 ; i < 2 ; i++) {
		if(isDifferentColorPawn(Color, piecesOnBoard[kingSquare - pawnAttack[i]]))
			return 1;
	}
	return 0;
}

bool Move (int Piece, int currentSquare, int destSquare, int *piecesOnBoard) {
	switch(Piece) {
		case WP:
		case BP:
			return pawnMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
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
			return kingMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
		case WQ:
		case BQ:
			return queenMove(pieceColor(Piece), currentSquare, destSquare, piecesOnBoard);
	}
	return 0;
}
