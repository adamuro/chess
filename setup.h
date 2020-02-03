#ifndef SETUP_H
#define SETUP_H

#include "common.h"

#define WindowWidth 640
#define WindowHeight 640

#define Black 232,169,23
#define White 245,231,200

enum Pieces {
	WP = 0, WR = 1, WN = 2, WB = 3, WK = 4, WQ = 5,
	BP = 6, BR = 7, BN = 8, BB = 9, BK = 10, BQ = 11,
	NP = 12
};

void boardSetup (RectangleShape *Board);
void importPiecesTextures (Texture *piecesImages);
void piecesSetup (int *piecesOnBoard);

#endif