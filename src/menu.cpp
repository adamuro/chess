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
	Window -> draw(this -> menuBackground);

	Window -> draw(this -> Buttons[Takeback]);
}

void menuData::Event (Vector2f Clicked) {
	if(this -> Buttons[Takeback].getGlobalBounds().contains(Clicked))
		printf("x\n");
}