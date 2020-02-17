#ifndef USER_INCLUDED
#define USER_INCLUDED

#include "common.hpp"
/* Set application icon */
void setIcon (RenderWindow *Window);
/* Check what part of the window was clicked and call proper function */
void onClickEvent(RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu);
void boardClick (Vector2i clickedPosition, gameData *Game, boardData *Board);
void menuClick (RenderWindow *Window, gameData *Game, boardData *Board, menuData *Menu);

#endif