#include "common.hpp"

int moveCount; // Need to figure out how to count moves.

int main () {
	RectangleShape Board [64];
	boardSetup(Board);

	Texture piecesTextures[12];
	importPiecesTextures(piecesTextures);

	int piecesOnBoard [64];
	piecesSetup(piecesOnBoard);

	int markedSquare = -1; // That means that no piece is marked at the time

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
			onClickEvent(clickedPosition, piecesOnBoard, &markedSquare);
		}
		/* U can still make move after move without clicking on the piece again */
		/* Try Window.GetEvent(windowEvent) or smt like that */
		drawBoard(&Window, Board);
		drawPieces(&Window, piecesTextures, piecesOnBoard);
		Window.display();
	}
	return 0;
}