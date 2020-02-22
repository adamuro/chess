#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.hpp"

using namespace sf;

class boardData {
	public:
		boardData ();
		~boardData () {};
		
		void boardSetup ();
		void piecesSetup ();
		void highlightSetup ();
		void importPiecesTextures ();

		void setHighlightPosition (int x, int y);
		void setPiecePosition (Sprite *Piece, int x, int y);
		void setPieceTexture (Sprite *Piece, int textureIndex);

		Texture getPieceTexture (int Piece);

		void drawBoardImage (RenderWindow *Window, int Index);
		void drawHighlight (RenderWindow *Window);
		void drawBoard (RenderWindow *Window);
		void drawPieces (RenderWindow *Window);

		int getPiece (int Square);
		int getPieceColor (int Square);
		int* getPiecesOnBoard ();
		
		int getMarkedSquare ();
		int getMarkedPiece ();

		int getClickedSquare ();
		int getClickedPiece ();

		void unmarkSquare ();
		void setMarkedSquare (int Square);
		void setClickedSquare (int Square);
		void setPiece (int Square, int Piece);

		bool checkMove (int destSquare);
		bool isSquareAttacked (int Square, int Color);
		bool inCheck (int Color);

		void moveUpdate ();

		Texture piecesTextures [14];
	private:
		RectangleShape boardImage [64];
		RectangleShape Highlight;
		
		int piecesOnBoard [64];
		int markedSquare;
		int clickedSquare;
};

#endif