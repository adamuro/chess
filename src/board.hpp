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
		int getMarkedSquare ();
		int getMarkedPiece ();

		void setMarkedSquare (int Square);
	
	private:
		Texture piecesTextures [12];
		RectangleShape boardImage [64];
		RectangleShape Highlight;
		
		int piecesOnBoard [64];
		int markedSquare;
};

#endif