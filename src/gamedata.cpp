#include "gamedata.hpp"

moveData::moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevPosition_, int currentPosition_)
:	moveNumber(moveNumber_),
	movedPiece(movedPiece_),
	takenPiece(takenPiece_),
	prevPosition(prevPosition_),
	currentPosition(currentPosition_) {}

gameData::gameData ()
:	playerToMove(1),
	moveCount(0),
	moveList(NULL) {}

void gameData::addMove (int movedPiece, int takenPiece, int prevPosition, int currentPosition) {
	moveData *currentMove = this -> moveList;

	while(this -> moveList != NULL) {
		this -> moveList = this -> moveList -> nextMove;
		currentMove = this -> moveList;
	}

	this -> moveList = new moveData(this -> moveCount++, movedPiece, takenPiece, prevPosition, currentPosition);
	this -> moveList -> prevMove = currentMove;
}

void gameData::changePlayer () {
	this -> playerToMove *= -1;
}

int gameData::getPlayer () {
	return this -> playerToMove;
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

int gameData::getMoveNumber () {
	return this -> moveCount;
}