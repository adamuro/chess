#include "menu.hpp"

menuData::menuData () {
	menuSetup ();
	importMenuTextures ();
}

void menuData::menuSetup () {
	this -> menuBackground.setSize(Vector2f(windowWidth - boardWidth, windowHeight));
	this -> menuBackground.setPosition(boardWidth, 0);
	this -> menuBackground.setFillColor(Color(colorMenuBackground));
}

void menuData::importMenuTextures () {
	this -> buttonTextures[Takeback].loadFromFile("./images/Takeback.png");
}

void menuData::drawMenu (RenderWindow *Window) {
	Window -> draw(this -> menuBackground);
}