#ifndef PAWN_HH
#define PAWN_HH

enum COLOR { BLANK, RED=1, WHITE };

enum PAWNTYPE { NONE, FREE, MEN=5, KING=10 };


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
		xPos = xCoord*107+73;
		yPos = yCoord*107+73;
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
