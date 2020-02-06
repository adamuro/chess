#ifndef GAMELOG_INCLUDED
#define GAMELOG_INCLUDED

#include "common.hpp"

class moveData {
	public:
		moveData (int Number, int Moved, int Taken, int posBefore, int posAfter, moveData *prevMove);
		void printMove ();
		int getMovedPiece ();
		int getPrevPosition ();
		int getCurrentPosition ();
	private:
		int moveNumber;
		int movedPiece;
		int takenPiece;
		int prevPosition;
		int currentPosition;

		moveData *nextMove;
		moveData *prevMove;
}

#endif