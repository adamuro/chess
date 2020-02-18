#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include <iostream>

class moveList {
	public:
		moveList (): movesNumber(0) {}
		~moveList () {}

		void addMove (int Square);
		void setMove (int Square);
		void increaseMovesNumber ();
		bool Contains (int Square);

		int getMove (int Index);
		int getMovesNumber ();

		moveList operator + (moveList const &obj);
	private:
		int Moves [32];
		int movesNumber;
};

#endif