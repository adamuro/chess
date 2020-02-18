#include "common.hpp"

int main () {
	gameData *Game = new gameData;
	menuData *Menu = new menuData;

	RenderWindow Window(VideoMode(windowWidth, windowHeight), "Chess");
	setIcon(&Window);

	while(Window.isOpen()) { // Main loop
		Event windowEvent;

		while(Window.pollEvent(windowEvent)) {
			if(windowEvent.type == Event::Closed)
				Window.close();
			if(windowEvent.type == Event::MouseButtonPressed && windowEvent.mouseButton.button == Mouse::Left)
				onClickEvent(&Window, Game, Menu);
		}
		Game -> Draw(&Window);
		Menu -> drawMenu(&Window);
		Window.display();
	}
	return 0;
}