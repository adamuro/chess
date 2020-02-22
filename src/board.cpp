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

void boardData::piecesSetup () {
	this -> piecesOnBoard[0] = BRL;
	this -> piecesOnBoard[7] = BRR;
	this -> piecesOnBoard[1] = this -> piecesOnBoard[6] = BN;
	this -> piecesOnBoard[2] = this -> piecesOnBoard[5] = BB;
	this -> piecesOnBoard[3] = BQ;
	this -> piecesOnBoard[4] = BK;

	this -> piecesOnBoard[56] = WRL;
	this -> piecesOnBoard[63] = WRR;
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

void boardData::importPiecesTextures () {
	this -> piecesTextures[WP].loadFromFile("./images/WhitePawn.png");
	this -> piecesTextures[WRL].loadFromFile("./images/WhiteRook.png");
	this -> piecesTextures[WRR].loadFromFile("./images/WhiteRook.png");
	this -> piecesTextures[WN].loadFromFile("./images/WhiteKnight.png");
	this -> piecesTextures[WB].loadFromFile("./images/WhiteBishop.png");
	this -> piecesTextures[WK].loadFromFile("./images/WhiteKing.png");
	this -> piecesTextures[WQ].loadFromFile("./images/WhiteQueen.png");
	this -> piecesTextures[BP].loadFromFile("./images/BlackPawn.png");
	this -> piecesTextures[BRL].loadFromFile("./images/BlackRook.png");
	this -> piecesTextures[BRR].loadFromFile("./images/BlackRook.png");
	this -> piecesTextures[BN].loadFromFile("./images/BlackKnight.png");
	this -> piecesTextures[BB].loadFromFile("./images/BlackBishop.png");
	this -> piecesTextures[BK].loadFromFile("./images/BlackKing.png");
	this -> piecesTextures[BQ].loadFromFile("./images/BlackQueen.png");
}

void boardData::setHighlightPosition (int x, int y) {
	int squareEdge = boardHeight / 8;
	this -> Highlight.setPosition(x * squareEdge, y * squareEdge);
}

void boardData::setPiecePosition (Sprite *Piece, int x, int y) {
	int squareEdge = boardHeight / 8;
	Piece -> setPosition(squareEdge * x, squareEdge * y);
}

void boardData::setPieceTexture (Sprite *Piece, int textureIndex) {
	Piece -> setTexture(this -> piecesTextures[textureIndex]);
}

Texture boardData::getPieceTexture (int Piece) {
	return this -> piecesTextures[Piece];
}

void boardData::drawBoardImage (RenderWindow *Window, int Index) {
	Window -> draw(this -> boardImage[Index]);
}

void boardData::drawHighlight (RenderWindow *Window) {
	Window -> draw(this -> Highlight);
}

void boardData::drawBoard (RenderWindow *Window) {
	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			if(i * 8 + j == getMarkedSquare()) {
				setHighlightPosition(j, i);
				drawHighlight(Window);
			}
			else {
				drawBoardImage(Window, j * 8 + i);
			}
		}
	}
}

void boardData::drawPieces (RenderWindow *Window) {
	Sprite pieceSprite;

	for(int i = 0 ; i < 8 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int Piece = getPiece(j * 8 + i);
			if(Piece != NP) {
				setPieceTexture(&pieceSprite, Piece);
				setPiecePosition(&pieceSprite, i, j);
				Window -> draw(pieceSprite);
			}
		}
	}
}

int boardData::getPiece (int Square) {
	return this -> piecesOnBoard[Square];
}

int boardData::getPieceColor (int Square) {
	int Piece = getPiece(Square);

	if(Piece >= 0 && Piece <= 6)
		return White;
	if(Piece >= 6 && Piece <= 13)
		return Black;
	return 0;
}

int* boardData::getPiecesOnBoard () {
	return this -> piecesOnBoard;
}

int boardData::getMarkedSquare () {
	return this -> markedSquare;
}

int boardData::getMarkedPiece () {
	if(getMarkedSquare() != -1)
		return this -> piecesOnBoard[this -> markedSquare];
	else
		return NP;
}

int boardData::getClickedSquare () {
	return this -> clickedSquare;
}

int boardData::getClickedPiece () {
	return this -> piecesOnBoard[this -> clickedSquare];
}

void boardData::unmarkSquare () {
	this -> markedSquare = -1;
}

void boardData::setMarkedSquare (int Square) {
	this -> markedSquare = Square;
}

void boardData::setClickedSquare (int Square) {
	this -> clickedSquare = Square;
}

void boardData::setPiece (int Square, int Piece) {
	this -> piecesOnBoard[Square] = Piece;
}

bool boardData::checkMove (int destSquare) {
	bool Outcome;

	int takenPiece = getPiece(destSquare);
	setPiece(destSquare, getMarkedPiece());
	setPiece(getMarkedSquare(), NP);

	Outcome = !isInCheck(getPieceColor(destSquare), getPiecesOnBoard());

	setPiece(getMarkedSquare(), getPiece(destSquare));
	setPiece(destSquare, takenPiece);

	return Outcome;
}

bool boardData::isSquareAttacked (int Square, int Color) {
	return isAttacked(Square, Color, getPiecesOnBoard());
}

bool boardData::inCheck (int Color) {
	return isInCheck(Color, getPiecesOnBoard());
}

void boardData::moveUpdate () {
	int Piece = getMarkedPiece();
	int Color = pieceColor(Piece);
	int squaresDif = getClickedSquare() - getMarkedSquare();
	int Distance = abs(squaresDif);

	if((Piece == WK || Piece == BK) && Distance != 1 && Distance != 7 && Distance != 8 && Distance != 9) {
		if(squaresDif > 0) {
			if(Piece == WK) {
				setPiece(63, NP);
				setPiece(getMarkedSquare(), NP);
				setPiece(getMarkedSquare() + 2, WK);
				setPiece(getMarkedSquare() + 1, WRR);
			}
			else {
				setPiece(7, NP);
				setPiece(getMarkedSquare(), NP);
				setPiece(getMarkedSquare() + 2, BK);
				setPiece(getMarkedSquare() + 1, BRR);
			}
		}
		else {
			if(Piece == WK) {
				setPiece(56, NP);
				setPiece(getMarkedSquare(), NP);
				setPiece(getMarkedSquare() - 2, WK);
				setPiece(getMarkedSquare() - 1, WRL);
			}
			else {
				setPiece(0, NP);
				setPiece(getMarkedSquare(), NP);
				setPiece(getMarkedSquare() - 2, BK);
				setPiece(getMarkedSquare() - 1, BRL);
			}
		}
	}
	else if((Piece == WP || Piece == BP) && (Distance == 7 || Distance == 9) && getClickedPiece() == NP) {
		setPiece(getClickedSquare() + 8 * Color, NP);
		setPiece(getClickedSquare(), getMarkedPiece());
		setPiece(getMarkedSquare(), NP);
	}
	else {
		setPiece(getClickedSquare(), getMarkedPiece());
		setPiece(getMarkedSquare(), NP);
	}
}