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
	moveList(NULL) {}

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
	this -> moveList = Move;
}

void gameData::setNextMove (moveData* Move) {
	this -> moveList -> nextMove = Move;
}

void gameData::setPrevMove (moveData* Move) {
	this -> moveList -> prevMove = Move;
}

moveData* gameData::getMove () {
	return this -> moveList;
}

moveData* gameData::getPrevMove () {
	return this -> moveList -> prevMove;
}

moveData* gameData::getNextMove () {
	return this -> moveList -> nextMove;
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
	if(this -> moveList != NULL) {
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
	return this -> moveList -> movedPiece;
}

int gameData::getCurrentSquare () {
	return this -> moveList -> currentSquare;
}

int gameData::getPrevSquare () {
	return this -> moveList -> prevSquare;
}

int gameData::getTakenPiece () {
	return this -> moveList -> takenPiece;
}

int gameData::getTakenSquare () {
	return this -> moveList -> takenSquare;
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

void gameData::printMove () {
	printf("%d\n", this -> moveList -> moveNumber);
	printf("%d\n", this -> moveList -> movedPiece);
	printf("%d\n", this -> moveList -> takenPiece);
	printf("%d\n", this -> moveList -> prevSquare);
	printf("%d\n", this -> moveList -> currentSquare);
}