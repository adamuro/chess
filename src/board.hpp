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
		void importPiecesTextures ();
		void piecesSetup ();
		void highlightSetup ();

		void drawBoard (RenderWindow *Window);
		void drawPieces (RenderWindow *Window);

		int getPiece (int Square);
		int getPieceColor (int Square);
		int* getPiecesOnBoard ();
		
		int getMarkedSquare ();
		int getMarkedPiece ();

		int getClickedSquare ();
		int getClickedPiece ();

		void setPiece (int Square, int Piece);
		void setMarkedSquare (int Square);
		void unmarkSquare ();
		void setClickedSquare (int Square);

		bool checkMove (int destSquare);
		bool isSquareAttacked (int Square, int Color);
		bool inCheck (int Color);

		void moveUpdate ();
	private:
		Texture piecesTextures [14];
		RectangleShape boardImage [64];
		RectangleShape Highlight;
		
		int piecesOnBoard [64];
		int markedSquare;
		int clickedSquare;
};

#endif