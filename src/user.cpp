#include "user.hpp"

int getClickedSquare(Vector2i clickedPosition) {
	int Column = (int)clickedPosition.x / 80; // How many squares fit
	int File = (int)clickedPosition.y / 80;   // in that number of pixels.
	int clickedSquare = Column + File * 8;	  // Convert column and file
											  // numbert into board index
	return clickedSquare;					  // 0 <= clickedSquare <= 63
}

void onClickEvent(Vector2i clickedPosition, int *piecesOnBoard, int *markedSquare) {
	int clickedSquare = getClickedSquare(clickedPosition);

	if(*markedSquare == -1) {							  // If there's no piece marked
		if(piecesOnBoard[clickedSquare] != NP)			  // and if a piece was clicked
			*markedSquare = piecesOnBoard[clickedSquare]; // mark the clicked piece.
	}
	/* If a piece was marked and any other square was clicked, try to move the piece to the clicked square. */
	if(Move(piecesOnBoard[*markedSquare], *markedSquare, clickedSquare, piecesOnBoard)) {
		*markedSquare = -1;		 			 // If the move was succesful,
	}										 // unmark the square.
	if(piecesOnBoard[clickedSquare] != NP) { // If the move was unseccesful,
		*markedSquare = clickedSquare;  	 // and a piece was clicked,
	}										 // mark the clicked piece.
	*markedSquare = -1;						 // Otherwise,
}											 //	unmark the piece.