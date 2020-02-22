#ifndef USER_INCLUDED
#define USER_INCLUDED

#include "common.hpp"
/* Set application icon */
void setIcon (RenderWindow *Window);
/* Check what part of the window was clicked and call proper function */
void onClickEvent(RenderWindow *Window, gameData *Game, menuData *Menu);
void boardClick (RenderWindow *Window, Vector2i clickedPosition, gameData *Game);
void menuClick (RenderWindow *Window, gameData *Game, menuData *Menu);

#endif