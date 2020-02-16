#include "time.hpp"

timeData::timeData ()
:	Player(White),
	Started(0) {
		whiteTime = seconds(gameDuration);
		blackTime = seconds(gameDuration);
		this -> whiteTimeText.setPosition(650, 400);
		this -> blackTimeText.setPosition(650, 240);
	}

void timeData::startGame () {
	this -> Started = 1;
	this -> gameClock.restart();
}

void timeData::changePlayer () {
	if(getPlayer() == White)
		this -> whiteTime -= getMoveTime();
	else
		this -> blackTime -= getMoveTime();
	
	this -> Player *= -1;
	this -> gameClock.restart();
}

void timeData::drawTime (RenderWindow *Window) {
	Time updatedWhiteTime;
	Time updatedBlackTime;

	if(gameStarted()) {
		switch(getPlayer()) {
			case White:
				updatedWhiteTime = getWhiteTime() - getMoveTime();
				updatedBlackTime = getBlackTime();
				break;
			case Black:
				updatedBlackTime = getBlackTime() - getMoveTime();
				updatedWhiteTime = getWhiteTime();
				break;
		}
	}
	this -> whiteTimeText.setString(to_string(updatedWhiteTime.asSeconds()));
	this -> blackTimeText.setString(to_string(updatedBlackTime.asSeconds()));
	this -> whiteTimeText.setCharacterSize(30);
	this -> whiteTimeText.setFillColor(Color(10,10,10));
	Font timeFont;
	timeFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");
	this -> whiteTimeText.setFont(timeFont);

	Window -> draw(whiteTimeText);
	Window -> draw(blackTimeText);
}

int timeData::getPlayer () {
	return this -> Player;
}

bool timeData::gameStarted () {
	return this -> Started;
}

Time timeData::getMoveTime () {
	return this -> gameClock.getElapsedTime();
}

Time timeData::getWhiteTime () {
	return this -> whiteTime;
}

Time timeData::getBlackTime () {
	return this -> blackTime;
}