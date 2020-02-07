#include "user.hpp"

int getClickedSquare(Vector2i clickedPosition) {
	int Column = (int)clickedPosition.x / 80; // How many squares fit
	int File = (int)clickedPosition.y / 80;   // in that number of pixels.
	int clickedSquare = Column + File * 8;	  // Convert column and file
											  // number into board index
	return clickedSquare;					  // 0 <= clickedSquare <= 63
}

void onClickEvent(Vector2i clickedPosition, int *piecesOnBoard, int *markedSquare, int *playerToMove, gameData *currentGame) {
	int clickedSquare = getClickedSquare(clickedPosition);
	int clickedPiece = piecesOnBoard[clickedSquare];

	if(*markedSquare == -1) {								// If there's no piece marked
		if(clickedPiece != NP)			  					// and a piece of current move's
			if(*playerToMove == pieceColor(clickedPiece)) 	// player's color was clicked,
				*markedSquare = clickedSquare;				// mark the clicked piece.
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	else if(*markedSquare != clickedSquare && Move(piecesOnBoard[*markedSquare], *markedSquare, clickedSquare, piecesOnBoard, currentGame)) {
		*markedSquare = -1;		 												// If the move was succesful,
		changePlayerToMove(playerToMove);										// change the player to move
		// Might use currentGame -> addMove here
	}																			// and unmark the square.
	else if(*playerToMove == White && clickedPiece >= 0 && clickedPiece <= 5){ 	// If the move was unseccesful,
		*markedSquare = clickedSquare; 										    // and it's white to move
	}																			// and a White piece was clicked
	else if(*playerToMove == Black && clickedPiece >= 6 && clickedPiece <= 11)  // mark the clicked piece.
		*markedSquare = clickedSquare;											// Same with Black.
	else																		// Otherwise,
		*markedSquare = -1;														// unmark the piece.
}