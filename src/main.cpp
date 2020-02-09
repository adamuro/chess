#include "common.hpp"

int main () {
	//RectangleShape menuBackground;
	//menuSetup(&menuBackground);

	RectangleShape Board [64];
	boardSetup(Board);

	Texture piecesTextures [12];
	importPiecesTextures(piecesTextures);

	int piecesOnBoard [64];
	piecesSetup(piecesOnBoard);

	int markedSquare = -1; // That means that no piece is marked at the time.

	RectangleShape Highlight;
	highlightSetup(&Highlight);

	gameData *Game = new gameData;

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
			onClickEvent(clickedPosition, piecesOnBoard, &markedSquare, Game);
		}
		drawBoard(&Window, Board, Highlight, markedSquare);
		drawPieces(&Window, piecesTextures, piecesOnBoard);
		//menuSetup(&Window);
		Window.display();
	}
	return 0;
}