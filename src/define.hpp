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

#define colorMenuBackground 230,230,230
#define colorMenuHighlight 200,200,200

#define gameDuration 600 // In seconds

enum Pieces {
	WP = 0, WRL = 1, WRR = 2, WN = 3, WB = 4, WK = 5, WQ = 6,	  // WhitePawn, WhiteRook etc.
	BP = 7, BRL = 8, BRR = 9, BN = 10, BB = 11, BK = 12, BQ = 13, // BlackPawn, BlackRook etc.
	NP = 14														  // NoPiece
};

enum Players {
	White = 1, Black = -1
};

enum menuButtons {
	Takeback = 0
};

#endif