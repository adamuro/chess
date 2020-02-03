#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "common.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, 0 otherwise */
bool Move(int Piece, int currentSquare, int destSquare, int *piecesOnBoard);

#endif