#ifndef GAMELOG_INCLUDED
#define GAMELOG_INCLUDED

#include <iostream>

class moveData {
	public:
		moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevPosition_, int currentPosition_);

		int moveNumber;
		int movedPiece;
		int takenPiece;
		int prevPosition;
		int currentPosition;

		moveData *nextMove;
		moveData *prevMove;
};

class gameData {
	public:
		gameData ();
		~gameData () {}

		void addMove (int movedPiece, int takenPiece, int prevPosition, int currentPosition);
		void printMove ();
		int getMoveNumber ();
		int getMovedPiece ();
		int getPrevPosition ();
		int getCurrentPosition ();
	private:
		int moveCount;
		moveData *moveList;
};

#endif