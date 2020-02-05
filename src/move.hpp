#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"
/* All functions return true if the move was succesful and false in the other case. */
bool pawnMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool rookMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool knightMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool bishopMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);

#endif