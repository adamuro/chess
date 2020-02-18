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

		void setMove (moveData* Move);
		void setNextMove (moveData* Move);
		void setPrevMove (moveData* Move);

		moveData* getMove ();
		moveData* getPrevMove ();
		moveData* getNextMove ();

		void moveBack (); // Go back to previous move.
		void deleteMove (moveData* Move); // Free Move memory.
		void Takeback (); // Delete current move and update Game and Board state.

		void changePlayer ();
		int getPlayer ();
		
		bool wasPieceMoved (int Piece); // Check if a Piece was moved during the game.
		bool movedLast (int Piece, int Square); // Check if Piece moved to Square in last move.
		
		int getMovedPiece ();
		int getCurrentSquare ();
		int getPrevSquare ();
		int getTakenPiece ();
		int getTakenSquare ();
		int getMoveDistance ();

		void increaseMoveCount ();
		void decreaseMoveCount ();
		int getMoveCount ();

		void printMove ();

		boardData Board;
	private:
		int Player;
		int moveCount;
		moveData *moveList;
};

#endif