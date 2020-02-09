#ifndef GAME_INCLUDED
#define GAME_INCLUDED

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
		void changePlayer ();
		int getPlayer ();
		
		bool wasPieceMoved (int Piece);
		bool movedLast (int Piece);
	private:
		int playerToMove;
		int moveCount;
		moveData *moveList;
};

#endif