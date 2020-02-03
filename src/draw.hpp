#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED

#include "common.hpp"

void drawBoard (RenderWindow *Window, RectangleShape *Board);
void drawPieces (RenderWindow *Window, Texture *piecesTextures, int *piecesOnBoard);

#endif