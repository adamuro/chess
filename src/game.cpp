#include "game.hpp"

moveData::moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevSquare_, int currentSquare_, int takenSquare_)
:	moveNumber(moveNumber_),
	movedPiece(movedPiece_),
	takenPiece(takenPiece_),
	prevSquare(prevSquare_),
	currentSquare(currentSquare_),
	takenSquare(takenSquare_),
	nextMove(NULL) {}

gameData::gameData ()
:	Player(White),
	moveCount(0),
	moveHistory(NULL) {}

void gameData::addMove (int movedPiece, int takenPiece, int prevSquare, int currentSquare) {
	moveData *currentMove = getMove();

	int Distance = abs(currentSquare - prevSquare);
	int takenSquare;

	if((movedPiece == WP || movedPiece == BP) && takenPiece == NP && (Distance == 7 || Distance == 9)) {
		takenPiece = (movedPiece == WP) ? BP : WP;
		takenSquare = currentSquare + 8 * pieceColor(movedPiece);
	}
	else
		takenSquare = currentSquare;

	while(getMove() != NULL) {
		currentMove = getMove();
		setMove(getNextMove());
	}

	setMove(new moveData(getMoveCount(), movedPiece, takenPiece, prevSquare, currentSquare, takenSquare));
	setPrevMove(currentMove);
	increaseMoveCount();

}

void gameData::setMove (moveData* Move) {
	this -> moveHistory = Move;
}

void gameData::setNextMove (moveData* Move) {
	this -> moveHistory -> nextMove = Move;
}

void gameData::setPrevMove (moveData* Move) {
	this -> moveHistory -> prevMove = Move;
}

moveData* gameData::getMove () {
	return this -> moveHistory;
}

moveData* gameData::getPrevMove () {
	return this -> moveHistory -> prevMove;
}

moveData* gameData::getNextMove () {
	return this -> moveHistory -> nextMove;
}

void gameData::deleteMove (moveData* Move) {
	delete Move;
}

void gameData::moveBack () {
	if(getMoveCount() == 1) {
			deleteMove(getMove());
			setMove(NULL);
			changePlayer();
		}
		else if(getMoveCount() > 1) {
			setMove(getPrevMove());
			deleteMove(getNextMove());
			setNextMove(NULL);
			changePlayer();
		}
}

void gameData::Takeback () {
	if(this -> moveHistory != NULL) {
		int movedPiece = getMovedPiece();
		int prevSquare = getPrevSquare();
		int currentSquare = getCurrentSquare();
		int takenPiece = getTakenPiece();
		int takenSquare = getTakenSquare();

		this -> Board.setPiece(prevSquare, movedPiece);
		this -> Board.setPiece(currentSquare, NP);
		this -> Board.setPiece(takenSquare, takenPiece);

		moveBack();
		decreaseMoveCount();
	}
}

void gameData::changePlayer () {
	this -> Player *= -1;
}

int gameData::getPlayer () {
	return this -> Player;
}

bool gameData::wasPieceMoved (int Piece) {
	moveData *Iterate = getMove();

	while(Iterate != NULL) {
		if(Iterate -> movedPiece == Piece)
			return 1;
		Iterate = Iterate -> prevMove;
	}
	return 0;
}

bool gameData::movedLast (int Piece, int Square) {
	return (getMovedPiece() == Piece && getCurrentSquare() == Square);
}

int gameData::getMovedPiece () {
	return this -> moveHistory -> movedPiece;
}

int gameData::getCurrentSquare () {
	return this -> moveHistory -> currentSquare;
}

int gameData::getPrevSquare () {
	return this -> moveHistory -> prevSquare;
}

int gameData::getTakenPiece () {
	return this -> moveHistory -> takenPiece;
}

int gameData::getTakenSquare () {
	return this -> moveHistory -> takenSquare;
}

int gameData::getMoveDistance () {
	int prevSquare = getPrevSquare();
	int currentSquare = getCurrentSquare();
	int Distance = abs(currentSquare - prevSquare);
	return Distance;
}

void gameData::increaseMoveCount () {
	this -> moveCount++;
}
void gameData::decreaseMoveCount () {
	this -> moveCount--;
}

int gameData::getMoveCount () {
	return this -> moveCount;
}

bool gameData::isLegalMove (moveList possibleMoves) {
	int destSquare = this -> Board.getClickedSquare();
	return (possibleMoves.Contains(destSquare));
}

bool gameData::Move () {
	int Piece = this -> Board.getMarkedPiece();
	
	switch(Piece) {
		case WP:
		case BP:
			return isLegalMove(pawnMoves());
		case WRL:
		case WRR:
		case BRL:
		case BRR:
			return isLegalMove(rookMoves());
		case WN:
		case BN:
			return isLegalMove(knightMoves());
		case WB:
		case BB:
			return isLegalMove(bishopMoves());
		case WK:
		case BK:
			return isLegalMove(kingMoves());
		case WQ:
		case BQ:
			return isLegalMove(queenMoves());
	}
	return 0;
}

/* Need to implement these functions using Piece and pieceColor(Piece) instead of Color */
moveList gameData::pawnMoves () {
	int Pawn = this -> Board.getMarkedPiece();
	int Color = pieceColor(Pawn);

	int currentSquare = this -> Board.getMarkedSquare();
	int nextSquare = currentSquare - 8 * Color;
	int takeLeftSquare = nextSquare - 1;
	int takeRightSquare = nextSquare + 1;
	int doubleMoveSquare = nextSquare - 8 * Color;
	int enPassantLeftSquare = currentSquare - 1;
	int enPassantRightSquare = currentSquare + 1;
	int enPassantLeftTakeSquare = enPassantLeftSquare - 8 * Color;
	int enPassantRightTakeSquare = enPassantRightSquare - 8 * Color;

	int nextPiece = this -> Board.getPiece(nextSquare);
	int doubleMovePiece = this -> Board.getPiece(doubleMoveSquare);
	int takeLeftPiece = this -> Board.getPiece(takeLeftSquare);
	int takeRightPiece = this -> Board.getPiece(takeRightSquare);
	int enPassantLeftPiece = this -> Board.getPiece(enPassantLeftSquare);
	int enPassantRightPiece = this -> Board.getPiece(enPassantRightSquare);

	moveList possibleMoves;

	if(nextPiece == NP && doubleMovePiece == NP) {
		if(isPawnStartingSquare(currentSquare, Color))
			if(this -> Board.checkMove(doubleMoveSquare))
				possibleMoves.addMove(doubleMoveSquare);
	}
	if(nextPiece == NP) {
		if(this -> Board.checkMove(nextSquare))
			possibleMoves.addMove(nextSquare);
	}
	/* NEXT 4 IFS COULD BE 1 FOR LOOP WITH 1 IF */
	if(isDifferentColor(takeLeftPiece, Color)) {
		if(this -> Board.checkMove(takeLeftSquare))
			possibleMoves.addMove(takeLeftSquare);
	}
	if(isDifferentColor(takeRightPiece, Color)) {
		if(this -> Board.checkMove(takeRightSquare))
			possibleMoves.addMove(takeRightSquare);
	}
	if(isDifferentColorPawn(enPassantLeftPiece, Color)) {
		if(this -> movedLast(enPassantLeftPiece, enPassantLeftSquare) && this -> getMoveDistance() == 16) {
			if(this -> Board.checkMove(enPassantLeftSquare)) {
				possibleMoves.addMove(enPassantLeftTakeSquare);	
			}
		}
	}
	if(isDifferentColorPawn(enPassantRightPiece, Color)) {
		if(this -> movedLast(enPassantRightPiece, enPassantRightSquare) && this -> getMoveDistance() == 16) {
			if(this -> Board.checkMove(enPassantRightSquare))
				possibleMoves.addMove(enPassantRightTakeSquare);
		}
	}

	return possibleMoves;
}

moveList gameData::rookMoves () {
	int Rook = this -> Board.getMarkedPiece();
	int Color = pieceColor(Rook);

	int currentSquare = this -> Board.getMarkedSquare();
	int distToLeftEdge = currentSquare % 8;
	int leftEdge = currentSquare - distToLeftEdge;
	int rightEdge = currentSquare - distToLeftEdge + 7;

	pair <int, int> moveSub [2] = {{-1, leftEdge}, {-8, 0}};
	pair <int, int> moveAdd [2] = {{1, rightEdge}, {8, 63}};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + get<0>(moveSub[i]) ; Square >= get<1>(moveSub[i]) ; Square += get<0>(moveSub[i])) {
			if(this -> Board.getPiece(Square) == NP) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(this -> Board.getPiece(Square), Color)) {
				if(this -> Board.checkMove(Square)) {
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
			if(this -> Board.getPiece(Square) == NP) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(this -> Board.getPiece(Square), Color)) {
				if(this -> Board.checkMove(Square)) {
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

moveList gameData::knightMoves () {
	int Knight = this -> Board.getMarkedPiece();
	int Color = pieceColor(Knight);
	int currentSquare = this -> Board.getMarkedSquare();
	int horizontalMoves [2] = {6, -10};
	int verticalMoves [2] = {15, -17};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - horizontalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 < 6) {
			int Piece = this -> Board.getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + horizontalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 > 1) {
			int Piece = this -> Board.getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare - verticalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 < 7) {
			int Piece = this -> Board.getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		int Square = currentSquare + verticalMoves[i];
		if(isOnBoard(Square) && currentSquare % 8 > 0) {
			int Piece = this -> Board.getPiece(Square);
			if(Piece == NP || isDifferentColor(Piece, Color))
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
		}
	}

	return possibleMoves;
}

moveList gameData::bishopMoves () {
	int Bishop = this -> Board.getMarkedPiece();
	int Color = pieceColor(Bishop);
	int currentSquare = this -> Board.getMarkedSquare();
	
	int moveLeft [2] = {7, -9};
	int moveRight [2] = {-7, 9};

	moveList possibleMoves;

	for(int i = 0 ; i < 2 ; i++) {
		for(int Square = currentSquare + moveLeft[i] ; isOnBoard(Square) && Square % 8 >= 0 && Square % 8 < 7 ; Square += moveLeft[i]) {
			if(this -> Board.getPiece(Square) == NP) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(this -> Board.getPiece(Square), Color)) {
				if(this -> Board.checkMove(Square)) {
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
			if(this -> Board.getPiece(Square) == NP) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(this -> Board.getPiece(Square), Color)) {
				if(this -> Board.checkMove(Square)) {
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

moveList gameData::kingMoves () {
	int King = this -> Board.getMarkedPiece();
	int Color = pieceColor(King);
	int currentSquare = this -> Board.getMarkedSquare();

	int allyRookLeft = (pieceColor(King) == White) ? WRL : BRL;
	int allyRookRight = (pieceColor(King) == White) ? WRR : BRR;
	
	int Moves [8] = {1, -1, 7, -7, 8, -8, 9, -9};

	moveList possibleMoves;

	for(int i = 0 ; i < 8 ; i++) {
		int Square = currentSquare + Moves[i];
		if(isOnBoard(Square)) {
			if(this -> Board.getPiece(Square) == NP) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
			else if(isDifferentColor(this -> Board.getPiece(Square), Color)) {
				if(this -> Board.checkMove(Square))
					possibleMoves.addMove(Square);
			}
		}
	}

	if(!(this -> wasPieceMoved(King) || this -> wasPieceMoved(allyRookLeft))) {
		if(!this -> Board.inCheck(Color) && this -> Board.getPiece(currentSquare - 4) == allyRookLeft) {
			if(!(this -> Board.isSquareAttacked(currentSquare - 1, Color) || this -> Board.isSquareAttacked(currentSquare - 2, Color))) {
				if(this -> Board.getPiece(currentSquare - 1) == NP && this -> Board.getPiece(currentSquare - 2) == NP && this -> Board.getPiece(currentSquare - 3) == NP) {
					possibleMoves.addMove(currentSquare - 2);
					possibleMoves.addMove(currentSquare - 3);
					possibleMoves.addMove(currentSquare - 4);
				}
			}
		}
	}

	if(!(this -> wasPieceMoved(King) || this -> wasPieceMoved(allyRookRight))) {
		if(!this -> Board.inCheck(Color) && this -> Board.getPiece(currentSquare + 3) == allyRookRight) {
			if(!(this -> Board.isSquareAttacked(currentSquare + 1, Color) || this -> Board.isSquareAttacked(currentSquare + 2, Color))) {
				if(this -> Board.getPiece(currentSquare + 1) == NP && this -> Board.getPiece(currentSquare + 2) == NP) {
					possibleMoves.addMove(currentSquare + 2);
					possibleMoves.addMove(currentSquare + 3);
				}
			}
		}
	}

	return possibleMoves;
}

moveList gameData::queenMoves () {	
	moveList diagonalMoves = bishopMoves();
	moveList linearMoves = rookMoves();

	moveList possibleMoves = diagonalMoves + linearMoves;

	return possibleMoves;
}