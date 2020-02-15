#include "menu.hpp"

menuData::menuData () {
	importTextures ();
	menuSetup ();
}

void menuData::menuSetup () {
	this -> menuBackground.setSize(Vector2f(windowWidth - boardWidth, windowHeight));
	this -> menuBackground.setPosition(boardWidth, 0);
	this -> menuBackground.setFillColor(Color(colorMenuBackground));

	this -> Buttons[Takeback].setTexture(buttonTextures[Takeback]);
	this -> Buttons[Takeback].setPosition(Vector2f(boardWidth + 20, windowHeight - 100));
}

void menuData::importTextures () {
	this -> buttonTextures[Takeback].loadFromFile("./images/Takeback.png");
}

void menuData::drawMenu (RenderWindow *Window) {
	drawBackground(Window);
	drawButtonHighlight(Window);
	drawButton(Window, Takeback);
}

void menuData::drawBackground (RenderWindow *Window) {
	Window -> draw(this -> menuBackground);
}

void menuData::drawButton (RenderWindow *Window, int Button) {
	Window -> draw(this -> Buttons[Button]);
}

bool menuData::buttonContains (Vector2f Position, int Button) {
	return (this -> Buttons[Button].getGlobalBounds().contains(Position));
}

void menuData::clickEvent (Vector2f Clicked, gameData *Game, boardData *Board) {
	if(buttonContains(Clicked, Takeback)) {
		Game -> Takeback(Board);
	}
}

Vector2f menuData::getMousePosition (RenderWindow *Window) {
	return Window -> mapPixelToCoords(Mouse::getPosition(*Window));
}

Vector2f menuData::getButtonSize (int Button) {
	Vector2f buttonSize(Buttons[Button].getTexture() -> getSize().x,
			 			Buttons[Button].getTexture() -> getSize().y);
	return buttonSize;
}

Vector2f menuData::getButtonPosition (int Button) {
	return this -> Buttons[Button].getPosition();
}

void menuData::drawButtonHighlight (RenderWindow *Window) {
	Vector2f mousePosition = getMousePosition(Window);
	if(buttonContains(mousePosition, Takeback)) {
		RectangleShape Highlight;
		Highlight.setSize(getButtonSize(Takeback));
		Highlight.setPosition(getButtonPosition(Takeback));
		Highlight.setFillColor(Color(colorMenuHighlight));
		Window -> draw(Highlight);
	}
}