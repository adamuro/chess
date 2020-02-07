#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "common.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, false otherwise. */
bool Move (int Piece, int currentSquare, int destSquare, int *piecesOnBoard);
/* All functions return true if the move was succesful and false in the other case. */
bool pawnMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool rookMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool knightMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool bishopMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool kingMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);
bool queenMove (int Color, int currentSquare, int destSquare, int *piecesOnBoard);

#endif