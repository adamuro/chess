#include "common.h"

int moveCount;

int main () {
	RectangleShape Board [64];
	boardSetup(Board);

	Texture piecesTextures[12];
	importPiecesTextures(piecesTextures);

	int piecesOnBoard [64];
	piecesSetup(piecesOnBoard);

	RenderWindow Window(VideoMode(windowWidth, windowHeight), "Chess");

	while(Window.isOpen()) {
		Event windowEvent;

		while (Window.pollEvent(windowEvent)) {
			if (windowEvent.type == Event::Closed)
			Window.close();
		}
		if(windowEvent.type == Event::MouseButtonPressed &&
		windowEvent.mouseButton.button == Mouse::Left) {
			//int columnClicked = (int)Mouse::getPosition(Window).x / 80;
			//int fileClicked = (int)Mouse::getPosition(Window).y / 80;
		}
		drawBoard(&Window, Board);
		drawPieces(&Window, piecesTextures, piecesOnBoard);
		Window.display();
	}
	return 0;
}