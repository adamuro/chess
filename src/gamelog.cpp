#include "gamelog.hpp"

moveData::moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevPosition_, int currentPosition_)
:	moveNumber(moveNumber_),
	movedPiece(movedPiece_),
	takenPiece(takenPiece_),
	prevPosition(prevPosition_),
	currentPosition(currentPosition_) {}

gameData::gameData () {
	this -> moveCount = 0;
	this -> moveList = NULL;
}

void gameData::addMove (int movedPiece, int takenPiece, int prevPosition, int currentPosition) {
	int moveNumber = this -> moveCount;
	moveData *newMove = new moveData(moveNumber, movedPiece, takenPiece, prevPosition, currentPosition);
	
	if(this -> moveList == NULL) {
		this -> moveList = newMove;
	}
	else {
		while(this -> moveList -> nextMove)
			this -> moveList = this -> moveList -> nextMove;

		this -> moveList -> nextMove = newMove;
		this -> moveList = this -> moveList -> nextMove;
	}
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