#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED

#include "common.hpp"

void drawBoard (RenderWindow *Window, RectangleShape *Board, Sprite markedSprite, int markedSquare);
void drawPieces (RenderWindow *Window, Texture *piecesTextures, int *piecesOnBoard);

#endif