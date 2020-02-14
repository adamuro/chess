#include "user.hpp"

int getClickedSquare (Vector2i clickedPosition) {
	int Column = (int)clickedPosition.x / 80; // How many squares fit
	int File = (int)clickedPosition.y / 80;   // in that number of pixels.
	int clickedSquare = Column + File * 8;	  // Convert column and file
											  // number into square index.
	return clickedSquare;					  // 0 <= clickedSquare <= 63
}

void onClickEvent (RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu) {
	Vector2i clickedPosition = Mouse::getPosition(*Window);
	if(clickedPosition.x < boardWidth)
		boardClick(clickedPosition, Game, Board);
	else {
		menuClick(Window, Game, Board, Menu);
		Board -> unmarkSquare();
	}
}

void boardClick (Vector2i clickedPosition, gameData *Game, boardData *Board) {
	Board -> setClickedSquare(getClickedSquare(clickedPosition));
	int clickedSquare = Board -> getClickedSquare();
	int clickedPiece = Board -> getClickedPiece();
	int markedSquare = Board -> getMarkedSquare();
	int markedPiece = Board -> getMarkedPiece();

	if(markedSquare == -1) {
		if(clickedPiece != NP)
			if(Game -> getPlayer() == pieceColor(clickedPiece))
				Board -> setMarkedSquare(clickedSquare);
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	else if(markedSquare != clickedSquare && Move(Board, Game)) {
		Game -> addMove(markedPiece, clickedPiece, markedSquare, clickedSquare);
		Game -> changePlayer();
		Board -> moveUpdate();
		Board -> unmarkSquare();
	}
	else if(Game -> getPlayer() == pieceColor(clickedPiece))
		Board -> setMarkedSquare(clickedSquare);
	else
		Board -> unmarkSquare();
}

void menuClick (RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu) {
	Vector2i clickedPosition = Mouse::getPosition(*Window);
	Vector2f Clicked = Window -> mapPixelToCoords(clickedPosition);
	Menu -> Event(Clicked, Game, Board);
} 