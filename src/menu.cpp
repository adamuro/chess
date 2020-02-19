#include "menu.hpp"

menuData::menuData () {
	importTextures ();
	menuSetup ();
}

void menuData::menuSetup () {
	this -> menuBackground.setSize(Vector2f(windowWidth - boardWidth, windowHeight));
	this -> menuBackground.setPosition(boardWidth, 0);
	this -> menuBackground.setFillColor(Color(colorMenuBackground));

	Texture buttonTexture;

	buttonTexture.loadFromFile("./images/Takeback.png");
	this -> Buttons[Takeback].setTexture(buttonTextures[Takeback]);
	this -> Buttons[Takeback].setPosition(Vector2f(boardWidth + 20, windowHeight - 100));

	buttonTexture.loadFromFile("./images/Restart.png");
	this -> Buttons[Restart].setTexture(buttonTextures[Restart]);
	this -> Buttons[Restart].setPosition(Vector2f(boardWidth + 92, windowHeight - 100));

	setupButtonHighlight();
}

void menuData::importTextures () {
	this -> buttonTextures[Takeback].loadFromFile("./images/Takeback.png");
	this -> buttonTextures[Restart].loadFromFile("./images/Restart.png");
}

void menuData::drawMenu (RenderWindow *Window) {
	drawBackground(Window);
	drawButtonHighlight(Window);
	drawButton(Window, Takeback);
	drawButton(Window, Restart);
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

void menuData::clickEvent (Vector2f Clicked, gameData *Game) {
	if(buttonContains(Clicked, Takeback)) {
		Game -> Takeback();
	}
	if(buttonContains(Clicked, Restart)) {
		delete Game;
		Game = new gameData;
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
		setButtonHighlight(Takeback);
		drawHighlight(Window);
	}
	if(buttonContains(mousePosition, Restart)) {
		setButtonHighlight(Restart);
		drawHighlight(Window);
	}
}

void menuData::setButtonHighlight (int Button) {
	this -> buttonHighlight.setSize(getButtonSize(Button));
	this -> buttonHighlight.setPosition(getButtonPosition(Button));
}

void menuData::setupButtonHighlight () {
	this -> buttonHighlight.setFillColor(Color(colorMenuHighlight));
}

void menuData::drawHighlight (RenderWindow *Window) {
	Window -> draw(this -> buttonHighlight);
}