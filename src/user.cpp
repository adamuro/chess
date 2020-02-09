#include "user.hpp"

int getClickedSquare(Vector2i clickedPosition) {
	int Column = (int)clickedPosition.x / 80; // How many squares fit
	int File = (int)clickedPosition.y / 80;   // in that number of pixels.
	int clickedSquare = Column + File * 8;	  // Convert column and file
											  // number into board index
	return clickedSquare;					  // 0 <= clickedSquare <= 63
}

void onClickEvent(Vector2i clickedPosition, gameData *Game, boardData *Board) {
	int clickedSquare = getClickedSquare(clickedPosition);
	int clickedPiece = Board -> getPiece(clickedSquare);
	int markedSquare = Board -> getMarkedSquare();
	int markedPiece = Board -> getMarkedPiece();

	if(markedSquare == -1) {
		if(clickedPiece != NP)
			if(Game -> getPlayer() == pieceColor(clickedPiece))
				Board -> setMarkedSquare(clickedSquare);
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	else if(markedSquare != clickedSquare && Move(clickedSquare, Board, Game)) {
		Game -> addMove(markedPiece, clickedPiece, markedSquare, clickedSquare);
		Game -> changePlayer();
		Board -> setMarkedSquare(-1);
	}
	else if(Game -> getPlayer() == pieceColor(clickedPiece))
		Board -> setMarkedSquare(clickedSquare);
	else
		Board -> setMarkedSquare(-1);
}