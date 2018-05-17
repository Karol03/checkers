#ifndef PLAYER_HH
#define PLAYER_HH
#include "Pawn.h"

enum PLAYERTYPE { MAN=1, AI };

/*
enum PAWNTYPE { NONE, MEN=1, KINGS=10 };

enum COLOR { RED=1, WHITE };

struct PAWN {
	int xCoord;
	int yCoord;
	PAWNTYPE type;
	COLOR color;
};
*/
class Player {

	PAWN pawn[12];

	public:
	const PLAYERTYPE playertype;
	const COLOR color;

	Player(PLAYERTYPE playertype, COLOR color): playertype(playertype)
	   										  , color(color) {
		if(color == RED) 
			setRedPawns();
		else
			setWhitePawns();
					
		for(int i=0; i<12; i++)
			pawn[i].type = MEN;
	}	
				
	bool makeMove(Player*);

	PAWN* getPawns() {
		return pawn;
	}

	PAWN& getPawn(int number) {
		return pawn[number];
	}

	private:
		void setRedPawns();
		void setWhitePawns();
		void AImakeMove();
		void MANmakeMove();
		bool checkIfBeating();
		bool checkIfAnyMoves(Player*);
	    bool checkIfOponentLine();	
};



#endif
