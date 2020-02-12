#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, false otherwise. */
bool Move (boardData *Board, gameData *Game);
/* All functions return true if the move was succesful and false in the other case. */
int* pawnMoves (boardData *Board, gameData *Game);
int* rookMoves (boardData *Board, gameData *Game);
int* knightMoves (boardData *Board, gameData *Game);
int* bishopMoves (boardData *Board, gameData *Game);
bool kingMove (int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame);
bool queenMove (int currentSquare, int destSquare, int *piecesOnBoard);

#endif