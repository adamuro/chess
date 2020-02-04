#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "common.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, 0 otherwise */
bool Move(int Piece, int currentSquare, int destSquare, int *piecesOnBoard);
void changePlayerToMove(int *playerToMove);
bool isDifferentColor (int Piece, int Color); // Check if piece color is different than Color.
int pieceColor (int Piece); // Return Piece color.

#endif