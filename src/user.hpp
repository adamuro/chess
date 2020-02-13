#ifndef USER_INCLUDED
#define USER_INCLUDED

#include "common.hpp"
/* Check if there'a a move request, or a new piece is marked by user. */
void onClickEvent(Vector2i clickedPosition, gameData *Game, boardData *Board, menuData *Menu);
void boardClick (Vector2i clickedPosition, gameData *Game, boardData *Board);
void menuClick (Vector2i clickedPosition, gameData *Game, boardData *Board, menuData *Menu);

#endif