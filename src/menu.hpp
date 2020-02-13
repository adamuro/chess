#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "define.hpp"
#include "game.hpp"
#include "board.hpp"

using namespace sf;

class menuData {
	public:
		menuData ();
		~menuData () {};

		void menuSetup ();
		void importTextures ();
		void drawMenu (RenderWindow *Window);
		void Event (Vector2f Clicked);

	private:
		RectangleShape menuBackground;
		Texture buttonTextures [1];
		Sprite Buttons [1];

};


#endif