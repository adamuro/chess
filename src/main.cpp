#include "common.h"

int MoveCount;

int main () {
	RectangleShape Board [64];
	boardSetup(Board);

	Texture piecesTextures[12];
	importPiecesTextures(piecesTextures);

	int piecesOnBoard [64];
	piecesSetup(piecesOnBoard);

	RenderWindow Window(sf::VideoMode(WindowWidth, WindowHeight), "Chess");

	while(Window.isOpen()) {
		Event event;

		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed)
			Window.close();
		}
		drawBoard(&Window, Board);
		drawPieces(&Window, piecesTextures, piecesOnBoard);
		Window.display();
	}
	return 0;
}