#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <iostream>
#include "logic.hpp"
#include "board.hpp"

class moveData {
	public:
		moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevPosition_, int currentPosition_, int takenPosition_);
		~moveData () {};

		int moveNumber;
		int movedPiece;
		int takenPiece;
		int prevPosition;
		int currentPosition;
		int takenPosition;

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
		
		bool movedLast (int Piece, int Square);
		bool wasPieceMoved (int Piece);
		int getMoveDistance ();

		void Takeback (boardData *Board);

		void printMove ();
	private:
		int playerToMove;
		int moveCount;
		moveData *moveList;
};

#endif