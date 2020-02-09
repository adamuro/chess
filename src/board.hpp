#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "define.hpp"

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
		int* getPiecesOnBoard ();
		
		int getMarkedSquare ();
		int getMarkedPiece ();
		int getMarkedPieceColor ();

		int getClickedSquare ();
		int getClickedPiece ();

		void setMarkedSquare (int Square);
		void setClickedSquare (int Square);

		void checkMove (int destSquare);
		void checkDone (int destSquare);

		void moveUpdate ();
		void moveUndo ();
	
	private:
		Texture piecesTextures [12];
		RectangleShape boardImage [64];
		RectangleShape Highlight;
		
		int piecesOnBoard [64];
		int markedSquare;
		int clickedSquare;
		int takenPiece;
};

#endif