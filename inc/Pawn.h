#ifndef PAWN_HH
#define PAWN_HH

enum COLOR { RED=1, WHITE };

enum PAWNTYPE { NONE, MEN=1, KING=10 };


struct PAWN {
	int xCoord;
	int yCoord;
	PAWNTYPE type;
	COLOR color;
};

#endif
