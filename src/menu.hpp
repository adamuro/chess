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
		void importMenuTextures ();
		void drawMenu (RenderWindow *Window);

	private:
		RectangleShape menuBackground;
		Texture buttonTextures [1];

};


#endif