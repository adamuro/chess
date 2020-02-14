#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include <iostream>
#include "define.hpp"

int pieceColor (int Piece); // Return Piece color.

bool isDifferentColor (int Piece, int Color); // Check if Piece color is different than Color.
bool isSameColor (int Piece, int Color);
bool isOnBoard (int Square);

bool isAttacked (int checkSquare, int Color, int *piecesOnBoard); // Return true if Color(white or black) king is in check and false in the other case.
bool isInCheck (int Color, int *piecesOnBoard);

bool isPawnStartingSquare (int Color, int Square);

bool isDifferentColorPawn (int Color, int Piece);
bool isDifferentColorRook (int Color, int Piece);
bool isDifferentColorKnight (int Color, int Piece);
bool isDifferentColorBishop (int Color, int Piece);
bool isDifferentColorQueen (int Color, int Piece);
bool isDifferentColorKing (int Piece, int Color);
bool isDiffColorBNPK (int Piece, int Color);
bool isDiffColorRNPK (int Piece, int Color);

#endif