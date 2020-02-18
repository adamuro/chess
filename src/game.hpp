#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <iostream>
#include <utility>
#include "logic.hpp"
#include "board.hpp"
#include "move.hpp"

using namespace std;
using namespace sf;

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

		void Draw (RenderWindow *Window);
		void drawPossibleMoves (RenderWindow *Window);

		void addMove (int movedPiece, int takenPiece, int prevSquare, int currentSquare);

		void setMove (moveData* Move);
		void setNextMove (moveData* Move);
		void setPrevMove (moveData* Move);

		moveData* getMove ();
		moveData* getPrevMove ();
		moveData* getNextMove ();

		void deleteMove (moveData* Move);
		void moveBack (); // Delete current move and set previous move as current.
		void Takeback (); // Change Game and Board data to previous move state.

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

		bool Move (); // Try to move marked piece to clicked square.
		bool isLegalMove (moveList possibleMoves); // Check if destSquare is on the possibleMoves list.
		/* All functions below return the list of possible moves of currently marked piece */
		moveList pawnMoves ();
		moveList rookMoves ();
		moveList knightMoves ();	
		moveList bishopMoves ();
		moveList kingMoves ();
		moveList queenMoves ();

		boardData Board; // Information about current pieces position, textures.
	private:
		int Player;
		int moveCount;
		moveData *moveHistory;
};

#endif