#ifndef DRAW_H
#define DRAW_H

#include "common.h"

void drawBoard (RenderWindow *Window, RectangleShape *Board);
void drawPieces (RenderWindow *Window, Texture *piecesTextures, int *piecesOnBoard);

#endif