#include "user.hpp"

void setIcon (RenderWindow *Window) {
	Image Icon;
	Icon.loadFromFile("./images/Icon.png");
	Window -> setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
}

int getClickedSquare (Vector2i clickedPosition) {
	int Column = (int)clickedPosition.x / 80; 	// How many squares fit
	int File = (int)clickedPosition.y / 80;   	// in that number of pixels.
	int clickedSquare = Column + File * 8;	  	// Convert column and file
											  	// number into square index.
	return clickedSquare;					  	// 0 <= clickedSquare <= 63
}

void onClickEvent (RenderWindow *Window, gameData *Game, menuData *Menu) {
	Vector2i clickedPosition = Mouse::getPosition(*Window);
	if(clickedPosition.x < boardWidth)		// If any place on board was clicked,
		boardClick(clickedPosition, Game);	// call the board related click function.
	else {
		menuClick(Window, Game, Menu);		// Otherwise call the menu related function
		Game -> Board.unmarkSquare();		// and unmark board squares.
	}
}

void boardClick (Vector2i clickedPosition, gameData *Game) {
	Game -> Board.setClickedSquare(getClickedSquare(clickedPosition));
	int clickedSquare = Game -> Board.getClickedSquare();
	int clickedPiece = Game -> Board.getClickedPiece();
	int markedSquare = Game -> Board.getMarkedSquare();
	int markedPiece = Game -> Board.getMarkedPiece();

	if(markedSquare == -1) {									// If no square was marked
		if(clickedPiece != NP)									// and current players
			if(Game -> getPlayer() == pieceColor(clickedPiece))	// piece was clicked
				Game -> Board.setMarkedSquare(clickedSquare);		// mark the clicked square.
	}
	else if(markedSquare == clickedSquare) {	// If the clicked square was marked before,
		Game -> Board.unmarkSquare();			// unmark it.
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	else if(Game -> Move()) {
		Game -> addMove(markedPiece, clickedPiece, markedSquare, clickedSquare);
		Game -> changePlayer();			// If the move was possible
		Game -> Board.moveUpdate();		// add it to the list
		Game -> Board.unmarkSquare();	// and update game state.
	}
	else if(Game -> getPlayer() == pieceColor(clickedPiece))	// If current players other piece was clicked,
		Game -> Board.setMarkedSquare(clickedSquare);			// mark it.
	else
		Game -> Board.unmarkSquare(); // If none of those conditions was met, unmark board squares.
}

void menuClick (RenderWindow *Window, gameData *Game, menuData *Menu) {
	Vector2i clickedPosition = Mouse::getPosition(*Window);
	Vector2f Clicked = Window -> mapPixelToCoords(clickedPosition);
	Menu -> clickEvent(Clicked, Game);	// Get the needed type of vector and proceed the click function.
} 