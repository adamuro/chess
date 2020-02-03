#include "setup.h"

void boardSetup (RectangleShape *Board) {
	int squareEdge = WindowHeight / 8;
	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int squareNum = i * 8 + j;
			Board[squareNum].setSize(Vector2f(squareEdge, squareEdge));
			Board[squareNum].setPosition(squareEdge * i, squareEdge * j);
			if((squareNum + i) % 2)	
				Board[squareNum].setFillColor(Color(White));
			else
				Board[squareNum].setFillColor(Color(Black));
		}
	}
}

void importPiecesTextures (Texture *piecesImages) {
	piecesImages[WP].loadFromFile("./images/WhitePawn.png");
	piecesImages[WR].loadFromFile("./images/WhiteRook.png");
	piecesImages[WN].loadFromFile("./images/WhiteKnight.png");
	piecesImages[WB].loadFromFile("./images/WhiteBishop.png");
	piecesImages[WK].loadFromFile("./images/WhiteKing.png");
	piecesImages[WQ].loadFromFile("./images/WhiteQueen.png");
	piecesImages[BP].loadFromFile("./images/BlackPawn.png");
	piecesImages[BR].loadFromFile("./images/BlackRook.png");
	piecesImages[BN].loadFromFile("./images/BlackKnight.png");
	piecesImages[BB].loadFromFile("./images/BlackBishop.png");
	piecesImages[BK].loadFromFile("./images/BlackKing.png");
	piecesImages[BQ].loadFromFile("./images/BlackQueen.png");
}

void piecesSetup (int *piecesOnBoard) {
	piecesOnBoard[0] = piecesOnBoard[7] = BR;
	piecesOnBoard[1] = piecesOnBoard[6] = BN;
	piecesOnBoard[2] = piecesOnBoard[5] = BB;
	piecesOnBoard[3] = BK;
	piecesOnBoard[4] = BQ;

	piecesOnBoard[56] = piecesOnBoard[63] = WR;
	piecesOnBoard[57] = piecesOnBoard[62] = WN;
	piecesOnBoard[58] = piecesOnBoard[61] = WB;
	piecesOnBoard[59] = WK;
	piecesOnBoard[60] = WQ;

	for(int i = 8 ; i < 16 ; i++) {
		piecesOnBoard[i] = BP;
		piecesOnBoard[63 - i] = WP;
	}

	for(int i = 16 ; i < 48 ; i++)
		piecesOnBoard[i] = NP;
}