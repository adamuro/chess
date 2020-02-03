#include "common.hpp"

int moveCount;

int main () {
	RectangleShape Board [64];
	boardSetup(Board);

	Texture piecesTextures[12];
	importPiecesTextures(piecesTextures);

	int piecesOnBoard [64];
	piecesSetup(piecesOnBoard);

	int markedPiecePosition = -1; // That means that no piece is marked at the time

	RenderWindow Window(VideoMode(windowWidth, windowHeight), "Chess");

	while(Window.isOpen()) {
		Event windowEvent;

		while (Window.pollEvent(windowEvent)) {
			if (windowEvent.type == Event::Closed)
			Window.close();
		}

		if(windowEvent.type == Event::MouseButtonPressed &&
		windowEvent.mouseButton.button == Mouse::Left) {
			Vector2i clickedPosition = Mouse::getPosition(Window);
			markedPiecePosition = newPositionMarked(clickedPosition, piecesOnBoard);
			printf("%d\n", markedPiecePosition);
		}

		drawBoard(&Window, Board);
		drawPieces(&Window, piecesTextures, piecesOnBoard);
		Window.display();
	}
	return 0;
}