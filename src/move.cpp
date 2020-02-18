#include "move.hpp"

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