#include "move.hpp"

using namespace std;

bool isLegalMove (int destSquare, moveList possibleMoves) {
	return (possibleMoves.Contains(destSquare));
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
		case WQ:
		case BQ:
			return isLegalMove(destSquare, queenMoves(Board, Game));
	}
	return 0;
}

/* Need to implement these functions using Piece and pieceColor(Piece) instead of Color */
moveList pawnMoves (boardData *Board, gameData *Game) {
	int Pawn = Board -> getMarkedPiece();
	int Color = pieceColor(Pawn);

	int currentSquare = Board -> getMarkedSquare();
	int nextSquare = currentSquare - 8 * Color;
	int takeLeftSquare = nextSquare - 1;
	int takeRightSquare = nextSquare + 1;
	int doubleMoveSquare = nextSquare - 8 * Color;
	int enPassantLeftSquare = currentSquare - 1;
	int enPassantRightSquare = currentSquare + 1;
	int enPassantLeftTakeSquare = enPassantLeftSquare - 8 * Color;
	int enPassantRightTakeSquare = enPassantRightSquare - 8 * Color;

	int nextPiece = Board -> getPiece(nextSquare);
	int doubleMovePiece = Board -> getPiece(doubleMoveSquare);
	int takeLeftPiece = Board -> getPiece(takeLeftSquare);
	int takeRightPiece = Board -> getPiece(takeRightSquare);
	int enPassantLeftPiece = Board -> getPiece(enPassantLeftSquare);
	int enPassantRightPiece = Board -> getPiece(enPassantRightSquare);

	moveList possibleMoves;

	if(nextPiece == NP && doubleMovePiece == NP) {
		if(isPawnStartingSquare(currentSquare, Color))
			if(Board -> checkMove(doubleMoveSquare))
				possibleMoves.addMove(doubleMoveSquare);
	}
	if(nextPiece == NP) {
		if(Board -> checkMove(nextSquare))
			possibleMoves.addMove(nextSquare);
	}
	/* NEXT 4 IFS COULD BE 1 FOR LOOP WITH 1 IF */
	if(isDifferentColor(takeLeftPiece, Color)) {
		if(Board -> checkMove(takeLeftSquare))
			possibleMoves.addMove(takeLeftSquare);
	}
	if(isDifferentColor(takeRightPiece, Color)) {
		if(Board -> checkMove(takeRightSquare))
			possibleMoves.addMove(takeRightSquare);
	}
	if(isDifferentColorPawn(enPassantLeftPiece, Color)) {
		if(Game -> movedLast(enPassantLeftPiece, enPassantLeftSquare) && Game -> getMoveDistance() == 16) {
			if(Board -> checkMove(enPassantLeftSquare)) {
				possibleMoves.addMove(enPassantLeftTakeSquare);	
			}
		}
	}
	if(isDifferentColorPawn(enPassantRightPiece, Color)) {
		if(Game -> movedLast(enPassantRightPiece, enPassantRightSquare) && Game -> getMoveDistance() == 16) {
			if(Board -> checkMove(enPassantRightSquare))
				possibleMoves.addMove(enPassantRightTakeSquare);
		}
	}

	return possibleMoves;
}

moveList rookMoves (boardData *Board, gameData *Game) {
	int Rook = Board -> getMarkedPiece();
	int Color = pieceColor(Rook);

	int currentSquare = Board -> getMarkedSquare();
	int distToLeftEdge = currentSquare % 8;
	int leftEdge = currentSquare - distToLeftEdge;
	int rightEdge = currentSquare - distToLeftEdge + 7;

	pair <int, int> moveSub [2] = {{-1, leftEdge}, {-8, 0}};
	pair <int, int> moveAdd [2] = {{1, rightEdge}, {8, 63}};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + get<0>(moveSub[i]) ; Square >= get<1>(moveSub[i]) ; Square += get<0>(moveSub[i])) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves.addMove(Square);
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
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves.addMove(Square);
					break;
				}
			}
			else
				break;
		}
	}

	return possibleMoves;
}

moveList knightMoves (boardData *Board, gameData *Game) {
	int Knight = Board -> getMarkedPiece();
	int Color = pieceColor(Knight);
	int currentSquare = Board -> getMarkedSquare();
	int horizontalMoves [2] = {6, -10};
	int verticalMoves [2] = {15, -17};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - horizontalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 < 6) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + horizontalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 > 1) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - verticalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 < 7) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + verticalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 > 0) {
			int Piece = Board -> getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	return possibleMoves;
}

moveList bishopMoves (boardData *Board, gameData *Game) {
	int Bishop = Board -> getMarkedPiece();
	int Color = pieceColor(Bishop);
	int currentSquare = Board -> getMarkedSquare();
	
	int moveLeft [2] = {7, -9};
	int moveRight [2] = {-7, 9};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + moveLeft[i] ; isOnBoard(Square) && Square % 8 >= 0 && Square % 8 < 7 ; Square += moveLeft[i]) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves.addMove(Square);
					break;
				}
			}
			else
				break;
		}
	}
	
	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + moveRight[i] ; isOnBoard(Square) && Square % 8 <= 7 && Square % 8 > 0 ; Square += moveRight[i]) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square)) {
					possibleMoves.addMove(Square);
					break;
				}
			}
			else
				break;
		}
	}
	
	return possibleMoves;
}

moveList kingMoves (boardData *Board, gameData *Game) {
	int King = Board -> getMarkedPiece();
	int Color = pieceColor(King);
	int currentSquare = Board -> getMarkedSquare();

	int allyRookLeft = (pieceColor(King) == White) ? WRL : BRL;
	int allyRookRight = (pieceColor(King) == White) ? WRR : BRR;
	
	int Moves [8] = {1, -1, 7, -7, 8, -8, 9, -9};

	moveList possibleMoves;

	for(int i = 0 ; i < 8 ; i++) {
		int Square = currentSquare + Moves[i];
		if(isOnBoard(Square)) {
			if(Board -> getPiece(Square) == NP) {
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(Board -> getPiece(Square), Color)) {
				if(Board -> checkMove(Square))
					possibleMoves.addMove(Square);
			}
		}
	}

	if(!(Game -> wasPieceMoved(King) || Game -> wasPieceMoved(allyRookLeft))) {
		if(!Board -> inCheck(Color) && Board -> getPiece(currentSquare - 4) != NP) {
			if(!(Board -> isSquareAttacked(currentSquare - 1, Color) || Board -> isSquareAttacked(currentSquare - 2, Color))) {
				if(Board -> getPiece(currentSquare - 1) == NP && Board -> getPiece(currentSquare - 2) == NP && Board -> getPiece(currentSquare - 3) == NP) {
					possibleMoves.addMove(currentSquare - 2);
					possibleMoves.addMove(currentSquare - 3);
					possibleMoves.addMove(currentSquare - 4);
				}
			}
		}
	}

	if(!(Game -> wasPieceMoved(King) || Game -> wasPieceMoved(allyRookRight))) {
		if(!Board -> inCheck(Color) && Board -> getPiece(currentSquare + 3) != NP) {
			if(!(Board -> isSquareAttacked(currentSquare + 1, Color) || Board -> isSquareAttacked(currentSquare + 2, Color))) {
				if(Board -> getPiece(currentSquare + 1) == NP && Board -> getPiece(currentSquare + 2) == NP) {
					possibleMoves.addMove(currentSquare + 2);
					possibleMoves.addMove(currentSquare + 3);
				}
			}
		}
	}

	return possibleMoves;
}

moveList queenMoves (boardData *Board, gameData *Game) {	
	moveList diagonalMoves = bishopMoves(Board, Game);
	moveList linearMoves = rookMoves(Board, Game);

	moveList possibleMoves = diagonalMoves + linearMoves;

	return possibleMoves;
}

void moveList::addMove (int Square) {
	setMove(Square);
	increaseMovesNumber();
}

void moveList::setMove (int Square) {
	this -> Moves[getMovesNumber()] = Square;
}

bool moveList::Contains (int Square) {
	for(int i = 0 ; i < getMovesNumber() ; i++) {
		if(getMove(i) == Square)
			return 1;
	}
	return 0;
}

int moveList::getMove (int Index) {
	return this -> Moves[Index];
}

int moveList::getMovesNumber () {
	return this -> movesNumber;
}

void moveList::increaseMovesNumber () {
	this -> movesNumber++;
}

moveList moveList::operator + (moveList const &obj) {
	moveList possibleMoves;

	for(int i = 0 ; i < getMovesNumber() ; i++)
		possibleMoves.addMove(Moves[i]);

	for(int i = 0 ; i < obj.movesNumber ; i++)
		possibleMoves.addMove(obj.Moves[i]);

	return possibleMoves;
}