#ifndef USER_INCLUDED
#define USER_INCLUDED

#include "common.hpp"
/* Check if there'a a move request, or a new piece is marked by user. */
void onClickEvent(Vector2i clickedPosition, int *piecesOnBoard, int *markedSquare, int *playerToMove, gameData *currentGame);

#endif