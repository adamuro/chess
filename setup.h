#ifndef SETUP_H
#define SETUP_H

#include "common.h"

#define WindowWidth 640
#define WindowHeight 640

#define Black 232,169,23
#define White 245,231,200

void boardSetup (RectangleShape *Board);
void piecesSetup (string *piecesOnBoard);
void drawBoard (RenderWindow *Window, RectangleShape *Board);
void drawPieces (RenderWindow *window, string *piecesOnBoard);

#endif