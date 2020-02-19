#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "define.hpp"
#include "game.hpp"

using namespace sf;

class menuData {
	public:
		menuData ();
		~menuData () {};

		void menuSetup ();
		void importTextures ();

		void drawMenu (RenderWindow *Window);
		void drawBackground (RenderWindow *Window);
		void drawButtonHighlight (RenderWindow *Window);
		void drawButton (RenderWindow *Window, int Button);

		bool buttonContains (Vector2f Position, int Button);
		bool buttonClicked (Vector2f Clicked, int Button);

		Vector2f getButtonSize (int Button);
		Vector2f getButtonPosition (int Button);
		Vector2f getMousePosition (RenderWindow *Window);

		void clickEvent (Vector2f Clicked, gameData *Game);
	private:
		RectangleShape menuBackground;
		Texture buttonTextures [2];
		Sprite Buttons [2];
};


#endif