#include "common.hpp"
#include "board.hpp"
#include "game.hpp"

int main () {
	gameData *Game = new gameData;
	boardData *Board = new boardData;

	RenderWindow Window(VideoMode(windowWidth, windowHeight), "Chess");

	while(Window.isOpen()) { // Main loop
		Event windowEvent;

		while (Window.pollEvent(windowEvent)) {
			if (windowEvent.type == Event::Closed)
			Window.close();
		}

		if(windowEvent.type == Event::MouseButtonReleased &&
		windowEvent.mouseButton.button == Mouse::Left) {
			Vector2i clickedPosition = Mouse::getPosition(Window);
			onClickEvent(clickedPosition, Game, Board);
		}
		Board -> drawBoard(&Window);
		Board -> drawPieces(&Window);
		Window.display();
	}
	return 0;
}