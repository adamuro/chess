#include "gamedata.hpp"

moveData::moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevPosition_, int currentPosition_)
:	moveNumber(moveNumber_),
	movedPiece(movedPiece_),
	takenPiece(takenPiece_),
	prevPosition(prevPosition_),
	currentPosition(currentPosition_) {}

gameData::gameData ()
:	moveCount(0),
	moveList(NULL) {}

void gameData::addMove (int movedPiece, int takenPiece, int prevPosition, int currentPosition) {
	moveData *currentMove = this -> moveList;

	while(this -> moveList != NULL)
		this -> moveList = this -> moveList -> nextMove;

	this -> moveList = new moveData(this -> moveCount++, movedPiece, takenPiece, prevPosition, currentPosition);
	this -> moveList -> prevMove = currentMove;
}

bool gameData::wasPieceMoved (int Piece) {
	moveData *Iterate = this -> moveList;

	while(Iterate != NULL) {
		if(Iterate -> movedPiece == Piece)
			return 1;
		Iterate = Iterate -> prevMove;
	}
	return 0;
}

bool gameData::movedLast (int Piece) {
	return (this -> moveList -> movedPiece == Piece) ? 1 : 0;
}

void gameData::printMove () {
	printf("Move number: %d\nMoved piece: %d\nTaken piece: %d\nPrevious position: %d\nCurrent position: %d\n", 
			this -> moveList -> moveNumber, this -> moveList -> movedPiece, this -> moveList -> takenPiece, this -> moveList -> prevPosition, this -> moveList -> currentPosition);
}

int gameData::getMoveNumber () {
	return this -> moveCount;
}

int gameData::getMovedPiece () {
	return this -> moveList -> movedPiece;
}

int gameData::getPrevPosition () {
	return this -> moveList -> prevPosition;
}

int gameData::getCurrentPosition () {
	return this -> moveList -> currentPosition;
}