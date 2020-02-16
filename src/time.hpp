#ifndef TIME_INCLUDED
#define TIME_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "define.hpp"
#include "game.hpp"

using namespace std;
using namespace sf;

class timeData {
	public:
		timeData ();
		~timeData () {}

		void startGame ();
		void changePlayer ();
		void drawTime (RenderWindow *Window);

		int getPlayer ();
		bool gameStarted ();

		Time getMoveTime ();
		Time getWhiteTime ();
		Time getBlackTime ();
	private:
		int Player;
		bool Started;

		Time whiteTime;
		Time blackTime;

		Text whiteTimeText;
		Text blackTimeText;

		Clock gameClock;
};

#endif