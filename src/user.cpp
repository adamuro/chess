#include "user.hpp"

int newPositionMarked(Vector2i clickedPosition, int *piecesOnBoard) {
	int Column = (int)clickedPosition.x / 80;
	int File = (int)clickedPosition.y / 80;
	int markedPiece = Column + File * 8;

	return (piecesOnBoard[markedPiece] != NP) ? markedPiece : -1;
}