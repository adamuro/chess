#include "common.h"

int MoveCount;
/*
class Piece {
	public:
		Piece(){}
		void setPosition(int Column, int File);
		virtual void move(int Column, int File) {}
	protected:
		int Side; // -1 for Black, 1 for White
		int currentColumn;	
		int currentFile;
};

class Pawn : private Piece {
	public:
		Pawn() {
			hasMoved = 0;
			enPassant = 0;
		}
		void move(int Column, int File) {
			if(Column == currentColumn && File == currentFile + Side)
				currentFile += Side;
			else if(Column == currentColumn &&
					File == currentFile + Side * 2 &&
					lastMove == MoveCount - 1) {
				currentFile += Side * 2;
			}
		}
	private:
		int lastMove;
};
*/

int main () {
	RectangleShape Board [64];
	boardSetup (Board);

	string piecesOnBoard [64] = {
		"BR", "BN", "BB", "BK", "BQ", "BB", "BN", "BR",
		"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP",
		"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ",
		"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ",
		"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ",
		"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ",
		"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP",
		"WR", "WN", "WB", "WK", "WQ", "WB", "WN", "WR",
	};

	RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Chess");

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
			window.close();
		}
		for(int i = 0 ; i < 64 ; i++)
			window.draw(Board[i]);
		
		window.display();
	}
	return 0;
}