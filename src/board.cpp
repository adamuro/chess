#include "board.hpp"

boardData::boardData () : markedSquare(-1) {
	boardSetup ();
	piecesSetup ();
	highlightSetup ();
	importPiecesTextures ();
}

void boardData::boardSetup () {
	int squareEdge = boardHeight / 8;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int squareNum = i * 8 + j;
			this -> boardImage[squareNum].setSize(Vector2f(squareEdge, squareEdge));
			this -> boardImage[squareNum].setPosition(squareEdge * i, squareEdge * j);
			if((squareNum + i) % 2)	
				this -> boardImage[squareNum].setFillColor(Color(colorWhite));
			else
				this -> boardImage[squareNum].setFillColor(Color(colorBlack));
		}
	}
}

void boardData::importPiecesTextures () {
	this -> piecesTextures[WP].loadFromFile("./images/WhitePawn.png");
	this -> piecesTextures[WR].loadFromFile("./images/WhiteRook.png");
	this -> piecesTextures[WN].loadFromFile("./images/WhiteKnight.png");
	this -> piecesTextures[WB].loadFromFile("./images/WhiteBishop.png");
	this -> piecesTextures[WK].loadFromFile("./images/WhiteKing.png");
	this -> piecesTextures[WQ].loadFromFile("./images/WhiteQueen.png");
	this -> piecesTextures[BP].loadFromFile("./images/BlackPawn.png");
	this -> piecesTextures[BR].loadFromFile("./images/BlackRook.png");
	this -> piecesTextures[BN].loadFromFile("./images/BlackKnight.png");
	this -> piecesTextures[BB].loadFromFile("./images/BlackBishop.png");
	this -> piecesTextures[BK].loadFromFile("./images/BlackKing.png");
	this -> piecesTextures[BQ].loadFromFile("./images/BlackQueen.png");
}

void boardData::piecesSetup () {
	this -> piecesOnBoard[0] = this -> piecesOnBoard[7] = BR;
	this -> piecesOnBoard[1] = this -> piecesOnBoard[6] = BN;
	this -> piecesOnBoard[2] = this -> piecesOnBoard[5] = BB;
	this -> piecesOnBoard[3] = BQ;
	this -> piecesOnBoard[4] = BK;

	this -> piecesOnBoard[56] = this -> piecesOnBoard[63] = WR;
	this -> piecesOnBoard[57] = this -> piecesOnBoard[62] = WN;
	this -> piecesOnBoard[58] = this -> piecesOnBoard[61] = WB;
	this -> piecesOnBoard[59] = WQ;
	this -> piecesOnBoard[60] = WK;

	for(int i = 8 ; i < 16 ; i++) {
		this -> piecesOnBoard[i] = BP;
		this -> piecesOnBoard[63 - i] = WP;
	}

	for(int i = 16 ; i < 48 ; i++)
		this -> piecesOnBoard[i] = NP;
}

void boardData::highlightSetup () {
	int squareEdge = boardHeight / 8;
	this -> Highlight.setSize(Vector2f(squareEdge, squareEdge));
	this -> Highlight.setFillColor(Color(colorHighlight));
}

void boardData::drawBoard (RenderWindow *Window) {
	int squareEdge = boardHeight / 8;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			if(i * 8 + j == this -> markedSquare) {
				this -> Highlight.setPosition(j * squareEdge, i * squareEdge);
				Window -> draw(this -> Highlight);
			}
			else {
				Window -> draw(this -> boardImage[j * 8 + i]);
			}
		}
	}
}

void boardData::drawPieces (RenderWindow *Window) {
	Sprite Piece;
	int squareEdge = boardHeight / 8;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int currentPiece = this -> piecesOnBoard[j * 8 + i];
			if(currentPiece != NP) {
				Piece.setTexture(this -> piecesTextures[currentPiece]);
				Piece.setPosition(i * squareEdge, j * squareEdge);
				Window -> draw(Piece);
			}
		}
	}
}

int boardData::getPiece(int Square) {
	return this -> piecesOnBoard[Square];
}

int boardData::getMarkedSquare () {
	return this -> markedSquare;
}

int boardData::getMarkedPiece () {
	return this -> piecesOnBoard[this -> markedSquare];
}

void boardData::setMarkedSquare (int Square) {
	this -> markedSquare = Square;
}