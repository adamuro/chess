#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"

class moveList {
	public:
		moveList (): movesNumber(0) {}
		~moveList () {}

		void addMove (int Square);
		void setMove (int Square);
		void increaseMovesNumber ();
		bool Contains (int Square);

		int getMove (int Index);
		int getMovesNumber ();

		moveList operator + (moveList const &obj);
	private:
		int Moves [32];
		int movesNumber;
};

bool Move (boardData *Board, gameData *Game); // Try to move marked piece to requested square.
bool isLegalMove (int destSquare, moveList possibleMoves); // Check if destSquare is on the possibleMoves list.
/* All functions below return the list of possible moves of currently marked piece */
moveList pawnMoves (boardData *Board, gameData *Game);
moveList rookMoves (boardData *Board, gameData *Game);
moveList knightMoves (boardData *Board, gameData *Game);	
moveList bishopMoves (boardData *Board, gameData *Game);
moveList kingMoves (boardData *Board, gameData *Game);
moveList queenMoves (boardData *Board, gameData *Game);

#endif