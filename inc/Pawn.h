#ifndef PAWN_HH
#define PAWN_HH

enum COLOR { BLANK, RED=1, WHITE };

enum PAWNTYPE { NONE, FREE, MEN=10, KING=100 };


struct PAWN {
	int xCoord;
	int yCoord;
	
	int xPos;
	int yPos;

	PAWNTYPE type;
	COLOR color;

	PAWN& operator=(const PAWN& pawn) {
		xCoord = pawn.xCoord;
		yCoord = pawn.yCoord;
		xPos = pawn.xPos;
		yPos = pawn.yPos;
		type = pawn.type;
		color = pawn.color;
		return *this;
	}

	void setCoord(int x, int y) {
		xCoord = x;
		yCoord = y;
		countPawnPosition();
	}

	void countPawnPosition() {
		xPos = xCoord*124;
		yPos = yCoord*124;
	}

	void erase() {
		xCoord = 0;
		yCoord = 0;
		xPos = 0;
		yPos = 0;
		type = FREE;
		color = BLANK;
	}
};

#endif
