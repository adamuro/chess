#ifndef USER_INCLUDED
#define USER_INCLUDED

#include "common.hpp"

void onClickEvent(RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu);
void boardClick (Vector2i clickedPosition, gameData *Game, boardData *Board);
void menuClick (RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu);

#endif