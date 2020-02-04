#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "common.hpp"
/* Try to move a piece from currentSquare to destSquare, */
/* Return true if the move was succesful, false otherwise. */
bool Move(int Piece, int currentSquare, int destSquare, int *piecesOnBoard);
void changePlayerToMove(int *playerToMove); // After every move.
bool isDifferentColor (int Piece, int Color); // Check if piece color is different than Color.
bool inSameColumn(int currentSquare, int destSquare); // Are the two squares in the same column?
bool inSameFile(int currentSquare, int destSquare); // Are the two squares in the same file?
int pieceColor (int Piece); // Return Piece color.

#endif