#ifndef DEFINE_INCLUDED
#define DEFINE_INCLUDED

#define windowWidth 900
#define windowHeight 640

#define boardWidth 640
#define boardHeight 640
/* Sqares colors */
#define colorBlack 232,169,23
#define colorWhite 245,231,200

#define colorHighlight 170,200,80

enum Pieces {
	WP = 0, WR = 1, WN = 2, WB = 3, WK = 4, WQ = 5,	  // WhitePawn, WhiteRook etc.
	BP = 6, BR = 7, BN = 8, BB = 9, BK = 10, BQ = 11, // BlackPawn, BlackRook etc.
	NP = 12											  // NoPiece
};

enum Players {
	White = 1, Black = -1
};

#endif