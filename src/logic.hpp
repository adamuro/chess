#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "common.hpp"

void changePlayerToMove(int *playerToMove); // After every move.
bool isDifferentColor (int Piece, int Color); // Check if piece color is different than Color.
bool inSameColumn(int currentSquare, int destSquare); // Are the two squares in the same column?
bool inSameFile(int currentSquare, int destSquare); // Are the two squares in the same file?
bool isAttacked (int checkSquare, int Color, int *piecesOnBoard); // Return true if Color(white or black) king is in check and false in the other case.
bool isInCheck (int Color, int *piecesOnBoard);
bool isPawnStartingSquare(int Color, int Square);
int pieceColor (int Piece); // Return Piece color.

bool isDifferentColorPawn (int Color, int Piece);
bool isDifferentColorRook (int Color, int Piece);
bool isDifferentColorKnight (int Color, int Piece);
bool isDifferentColorBishop (int Color, int Piece);
bool isDifferentColorQueen (int Color, int Piece);

#endif