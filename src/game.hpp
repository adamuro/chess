#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <iostream>
#include "logic.hpp"
#include "board.hpp"

class moveData {
	public:
		moveData (int moveNumber_, int movedPiece_, int takenPiece_, int prevSquare_, int currentSquare_, int takenSquare_);
		~moveData () {};

		int moveNumber;
		int movedPiece;
		int takenPiece;
		int prevSquare;
		int currentSquare;
		int takenSquare;

		moveData *nextMove;
		moveData *prevMove;
};

class gameData {
	public:
		gameData ();
		~gameData () {}

		void addMove (int movedPiece, int takenPiece, int prevSquare, int currentSquare);
		void changePlayer ();
		int getPlayer ();
		
		bool movedLast (int Piece, int Square);
		bool wasPieceMoved (int Piece);
		int getMovedPiece ();

		int getCurrentSquare ();
		int getPrevSquare ();
		int getTakenPiece ();
		int getTakenSquare ();
		int getMoveDistance ();

		void moveBack ();
		void deleteMove (moveData* Move);
		void Takeback (boardData *Board);

		void setMove (moveData* Move);
		void setNextMove (moveData* Move);
		void setPrevMove (moveData* Move);

		moveData* getMove ();
		moveData* getPrevMove ();
		moveData* getNextMove ();

		void increaseMoveCount ();
		void decreaseMoveCount ();
		int getMoveCount ();

		void printMove ();
	private:
		int playerToMove;
		int moveCount;
		moveData *moveList;
};

#endif