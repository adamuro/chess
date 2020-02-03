#ifndef SETUP_H
#define SETUP_H

#include "common.h"

#define WindowWidth 640
#define WindowHeight 640

#define Black 232,169,23
#define White 245,231,200

enum Pieces {
	NP = 0,
	WP = 1, WR = 2, WN = 3, WB = 4, WK = 5, WQ = 6,
	BP = 7, BR = 8, BN = 9, BB = 10, BK = 11, BQ = 12
};

void boardSetup (RectangleShape *Board);
void piecesSetup (int *piecesOnBoard);
void drawBoard (RenderWindow *Window, RectangleShape *Board);
void drawPieces (RenderWindow *window, string *piecesOnBoard);

#endif