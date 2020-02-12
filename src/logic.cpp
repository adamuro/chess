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
	if(Piece >= 0 && Piece <= 6)
		return White;
	if(Piece >= 6 && Piece <= 13)
		return Black;
	return 0;
}

bool inSameColumn (int currentSquare, int destSquare) {
	return !(abs(currentSquare - destSquare) % 8);
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
	if(Color == White && (Piece == BRL || Piece == BRR))
		return 1;
	if(Color == Black && (Piece == WRL || Piece == WRR))
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

bool isDifferentColorKing (int Color, int Piece) {
	if(Color == White && Piece == BK)
		return 1;
	if(Color == Black && Piece == WK)
		return 1;
	return 0;
}

bool isDiffColorBNPK (int Color, int Piece) {
	if(isDifferentColorBishop(Color, Piece) ||
	   isDifferentColorKnight(Color, Piece) ||
	   isDifferentColorPawn(Color, Piece) ||
	   isDifferentColorKing(Color, Piece))
		return 1;
	return 0;
}

bool isDiffColorRNPK (int Color, int Piece) {
	if(isDifferentColorRook(Color, Piece) ||
	   isDifferentColorKnight(Color, Piece) ||
	   isDifferentColorPawn(Color, Piece) ||
	   isDifferentColorKing(Color, Piece))
		return 1;
	return 0;
}

bool isPawnStartingSquare (int Color, int Square) {
	if(Color == White && Square >= 48 && Square < 56)
		return 1;
	if(Color == Black && Square >= 8 && Square < 16)
		return 1;
	return 0;
}

bool isAttacked (int checkSquare, int Color, int *piecesOnBoard) {
	int distToLeftEdge = checkSquare % 8;
	int leftEdge = checkSquare - distToLeftEdge;
	int rightEdge = checkSquare - distToLeftEdge + 7;

	int Diagonal[4] = {7, -7, 9, -9};
	int knightAttack[8] = {6, -6, 10, -10, 15, -15, 17, -17};
	int pawnAttack[2] = {7 * Color, 9 * Color};
	int kingAttack[8] = {1, -1, 7, -7, 8, -8, 9, -9};
	/* Searching for vertical and horizontal attacks on the king (queen or rook). */
	/* From the left */
	for(int i = checkSquare - 1 ; i >= leftEdge ; i--) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From the right */
	for(int i = checkSquare + 1 ; i <= rightEdge ; i++) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From above */
	for(int i = checkSquare + 8 ; i < 64 ; i+= 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* From beneath */
	for(int i = checkSquare - 8 ; i >= 0 ; i-= 8) {
		int Piece = piecesOnBoard[i];
		if(isSameColor(Piece, Color))
			break;
		if(isDiffColorBNPK(Color, Piece))
			break;
		if(isDifferentColorQueen(Color, Piece) || isDifferentColorRook(Color, Piece))
			return 1;
	}
	/* Searching for diagonal attacks on the king (queen or bishop). */
	for(int i = 0 ; i < 4 ; i++) {
		for(int j = checkSquare + Diagonal[i] ; j >= 0 && j < 64 ; j += Diagonal[i]) {
			int Piece = piecesOnBoard[j];
			if(isSameColor(piecesOnBoard[j], Color))
				break;
			if(isDiffColorRNPK(Color, Piece))
				break;
			if(isDifferentColorQueen(Color, Piece) || isDifferentColorBishop(Color, Piece))
				return 1;
		}
	}
	/* Searching for knights which attack the king */
	for(int i = 0 ; i < 8 ; i++) {
		int knightSquare = checkSquare + knightAttack[i];
		
		if(knightSquare >= 0 && knightSquare < 64)
			if(isDifferentColorKnight(Color, piecesOnBoard[knightSquare]))
				return 1;
	}
	/* Searching for pawns which attack the king */
	for(int i = 0 ; i < 2 ; i++) {
		int pawnSquare = checkSquare - pawnAttack[i];

		if(isDifferentColorPawn(Color, piecesOnBoard[pawnSquare]))
			return 1;
	}
	/* Searching for king which attacks the king */
	for(int i = 0 ; i < 8 ; i++) {
		int kingSquare = checkSquare - kingAttack[i];

		if(isDifferentColorKing(Color, piecesOnBoard[kingSquare]))
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