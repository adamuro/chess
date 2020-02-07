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
	int markedPiece = piecesOnBoard[*markedSquare];

	if(*markedSquare == -1) {								// If there's no piece marked
		if(clickedPiece != NP)			  					// and a piece of current move's
			if(*playerToMove == pieceColor(clickedPiece)) 	// player's color was clicked,
				*markedSquare = clickedSquare;				// mark the clicked piece.
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	else if(*markedSquare != clickedSquare && Move(markedPiece, *markedSquare, clickedSquare, piecesOnBoard, currentGame)) {
		currentGame -> addMove(markedPiece, clickedPiece, *markedSquare, clickedSquare);
		//currentGame -> printMove();
		*markedSquare = -1;		 												// If the move was succesful,
		changePlayerToMove(playerToMove);										// change the player to move
	}																			// and unmark the square.
	else if(*playerToMove == pieceColor(clickedPiece)){	 						// If the move was unseccesful,
		*markedSquare = clickedSquare; 										    // and the clicked piece is owned by current player,
	}																			// mark the clicked piece.
	else																		// Otherwise,
		*markedSquare = -1;														// unmark the piece.
}