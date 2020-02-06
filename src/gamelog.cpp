#include "gamelog.hpp"

moveData::~moveData () {
	this -> moveCount = 0;
	this -> List = NULL;
}

void gameData::addMove (int movedPiece, int takenPiece, int prevPosition, int currentPosition) {
	List -> moveNumber = moveCount++;
	List -> movedPiece = movedPiece;
	List -> takenPiece = takenPiece;
	List -> prevPosition = prevPosition;
	List -> currentPosition = currentPosition;
}

void gameData::printMove () {
	printf("Move number: %d\n
			Moved piece: %d\n
			Taken piece: %d\n
			Previous position: %d\n
			Current position: %d\n", 
			moveNumber, movedPiece, takenPiece, prevPosition, currentPosition);
}

int gameData::getMoveNumber () {
	return moveNumber;
}

int gameData::getMovedPiece () {
	return movedPiece;
}

int gameData::getPrevPosition () {
	return prevPosition;
}

int gameData::getCurrentPosition () {
	return currentPosition;
}
