#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"
#include "board.hpp"
#include "game.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, false otherwise. */
bool Move (int destSquare, boardData *Board, gameData *Game);
/* All functions return true if the move was succesful and false in the other case. */
bool pawnMove (int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame);
bool rookMove (int currentSquare, int destSquare, int *piecesOnBoard);
bool knightMove (int currentSquare, int destSquare, int *piecesOnBoard);
bool bishopMove (int currentSquare, int destSquare, int *piecesOnBoard);
bool kingMove (int currentSquare, int destSquare, int *piecesOnBoard, gameData *currentGame);
bool queenMove (int currentSquare, int destSquare, int *piecesOnBoard);

#endif