#ifndef GAMELOG_INCLUDED
#define GAMELOG_INCLUDED

#include "common.hpp"

typedef struct  {
	int moveNumber;
	int movedPiece;
	int takenPiece;
	int prevPosition;
	int currentPosition;

	moveData *nextMove;
	moveData *prevMove;
} List;

class gameData {
	public:
		gameData () {};
		~gameData () {};

		void addMove (int moveNumber, int movedPiece, int takenPiece, int prevPosition, int currentPosition);
		void printMove ();
		int getMovedPiece ();
		int getPrevPosition ();
		int getCurrentPosition ();
	private:
		int moveCount;
		List *moveList;
}

#endif