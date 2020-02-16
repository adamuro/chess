#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"

bool Move (boardData *Board, gameData *Game); // Try to move marked piece to requested square.
bool isLegalMove (int destSquare, int *possibleMoves); // Check if destSquare is on the possibleMoves list.
/* All functions below return the list of possible moves of currently marked piece */
int* pawnMoves (boardData *Board, gameData *Game);
int* rookMoves (boardData *Board, gameData *Game);
int* knightMoves (boardData *Board, gameData *Game);	
int* bishopMoves (boardData *Board, gameData *Game);
int* kingMoves (boardData *Board, gameData *Game);
int* queenMoves (boardData *Board, gameData *Game);
/*
class moveList {
	public:
		possibleMoves (): movesNumber(0) {};
		~possibleMoves () {};

		void addMove (int Square);
		void setMove (int Square);
		void increaseMovesNumber ();
		bool Contains (int Square);

		int getMove (int Index);
		int getMovesNumber ();
	private:
		int Moves [32];
		int movesNumber;
};
*/
#endif