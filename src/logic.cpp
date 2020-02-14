#include "logic.hpp"

int pieceColor (int Piece) {
	if(Piece >= 0 && Piece <= 6)
		return White;
	if(Piece >= 6 && Piece <= 13)
		return Black;
	return 0;
}

bool isDifferentColor (int Piece, int Color) {
	return (pieceColor(Piece) != Color && pieceColor(Piece));
}

bool isSameColor (int Piece, int Color) {
	return (pieceColor(Piece) == Color);
}

bool isOnBoard (int Square) {
	return (Square >= 0 && Square <= 63);
}

bool isPawnStartingSquare (int Square, int Color) {
	if(Color == White && Square >= 48 && Square < 56)
		return 1;
	if(Color == Black && Square >= 8 && Square < 16)
		return 1;
	return 0;
}


bool isDifferentColorQueen (int Piece, int Color) {
	if(Color == White && Piece == BQ)
		return 1;
	if(Color == Black && Piece == WQ)
		return 1;
	return 0;
}

bool isDifferentColorRook (int Piece, int Color) {
	if(Color == White && (Piece == BRL || Piece == BRR))
		return 1;
	if(Color == Black && (Piece == WRL || Piece == WRR))
		return 1;
	return 0;
}

bool isDifferentColorBishop (int Piece, int Color) {
	if(Color == White && Piece == BB)
		return 1;
	if(Color == Black && Piece == WB)
		return 1;
	return 0;
}

bool isDifferentColorKnight (int Piece, int Color) {
	if(Color == White && Piece == BN)
		return 1;
	if(Color == Black && Piece == WN)
		return 1;
	return 0;
}

bool isDifferentColorPawn (int Piece, int Color) {
	if(Color == White && Piece == BP)
		return 1;
	if(Color == Black && Piece == WP)
		return 1;
	return 0;
}

bool isDifferentColorKing (int Piece, int Color) {
	if(Color == White && Piece == BK)
		return 1;
	if(Color == Black && Piece == WK)
		return 1;
	return 0;
}

bool isDiffColorBNPK (int Piece, int Color) {
	if(isDifferentColorBishop(Piece, Color) ||
	   isDifferentColorKnight(Piece, Color) ||
	   isDifferentColorPawn(Piece, Color) ||
	   isDifferentColorKing(Piece, Color))
		return 1;
	return 0;
}

bool isDiffColorRNPK (int Piece, int Color) {
	if(isDifferentColorRook(Piece, Color) ||
	   isDifferentColorKnight(Piece, Color) ||
	   isDifferentColorPawn(Piece, Color) ||
	   isDifferentColorKing(Piece, Color))
		return 1;
	return 0;
}

bool isAttacked (int checkSquare, int Color, int *piecesOnBoard) {
	int distToLeftEdge = checkSquare % 8;
	int leftEdge = checkSquare - distToLeftEdge;
	int rightEdge = checkSquare - distToLeftEdge + 7;

	int Diagonal[4] = {7, -7, 9, -9};
	int horizontalKnightMoves [2] = {6, -10};
	int verticalKnightMoves [2] = {15, -17};
	int pawnAttack[2] = {7 * Color, 9 * Color};
	int kingAttack[8] = {1, -1, 7, -7, 8, -8, 9, -9};
	/* Searching for vertical and horizontal attacks on the king (queen or rook). */
	/* From the left */
	for(int i = checkSquare - 1 ; i >= leftEdge ; i--) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Piece, Color))
			break;
		if(isDifferentColorQueen(Piece, Color) || isDifferentColorRook(Piece, Color))
			return 1;
	}
	/* From the right */
	for(int i = checkSquare + 1 ; i <= rightEdge ; i++) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Piece, Color))
			break;
		if(isDifferentColorQueen(Piece, Color) || isDifferentColorRook(Piece, Color))
			return 1;
	}
	/* From above */
	for(int i = checkSquare + 8 ; isOnBoard(i) ; i += 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Piece, Color))
			break;
		if(isDifferentColorQueen(Piece, Color) || isDifferentColorRook(Piece, Color))
			return 1;
	}
	/* From beneath */
	for(int i = checkSquare - 8 ; isOnBoard(i) ; i -= 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Piece, Color))
			break;
		if(isDifferentColorQueen(Piece, Color) || isDifferentColorRook(Piece, Color))
			return 1;
	}
	/* Searching for diagonal attacks on the king (queen or bishop). */
	for(int i = 0 ; i < 4 ; i++) {
		for(int j = checkSquare + Diagonal[i] ; isOnBoard(j) ; j += Diagonal[i]) {
			int Piece = piecesOnBoard[j];
			if(isSameColor(piecesOnBoard[j], Color))
				break;
			if(isDiffColorRNPK(Piece, Color))
				break;
			if(isDifferentColorQueen(Piece, Color) || isDifferentColorBishop(Piece, Color))
				return 1;
		}
	}
	/* Searching for knights which attack the king */
	for(int i = 0 ; i < 2 ; i++) {
		int Square = checkSquare + horizontalKnightMoves[i];
		if(isOnBoard(Square) && Square % 8 < 6) {
			int Piece = piecesOnBoard[Square];
			if(isDifferentColorKnight(Piece, Color))
				return 1;
		}
	}
	for(int i = 0 ; i < 2 ; i++) {
		int Square = checkSquare - horizontalKnightMoves[i];
		if(isOnBoard(Square) && Square % 8 > 1) {
			int Piece = piecesOnBoard[Square];
			if(isDifferentColorKnight(Piece, Color))
				return 1;
		}
	}
	for(int i = 0 ; i < 2 ; i++) {
		int Square = checkSquare + verticalKnightMoves[i];
		if(isOnBoard(Square) && Square % 8 < 7) {
			int Piece = piecesOnBoard[Square];
			if(isDifferentColorKnight(Piece, Color))
				return 1;
		}
	}
	for(int i = 0 ; i < 2 ; i++) {
		int Square = checkSquare - verticalKnightMoves[i];
		if(isOnBoard(Square) && Square % 8 > 0) {
			int Piece = piecesOnBoard[Square];
			if(isDifferentColorKnight(Piece, Color))
				return 1;
		}
	}
	/* Searching for pawns which attack the king */
	for(int i = 0 ; i < 2 ; i++) {
		int pawnSquare = checkSquare - pawnAttack[i];
		if(isDifferentColorPawn(piecesOnBoard[pawnSquare], Color))
			return 1;
	}
	/* Searching for king which attacks the king */
	for(int i = 0 ; i < 8 ; i++) {
		int kingSquare = checkSquare - kingAttack[i];
		if(isDifferentColorKing(piecesOnBoard[kingSquare], Color))
			return 1;
	}

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
	return isAttacked(kingSquare, Color, piecesOnBoard);
}