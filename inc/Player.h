#ifndef PLAYER_HH
#define PLAYER_HH

enum PLAYERTYPE { MAN=1, AI };

enum PAWNTYPE { MEN=1, KINGS=10 };

enum COLOR { RED=1, WHITE };

struct POINT {
	int xCoord;
	int yCoord;
};

class Player {

	PAWNTYPE pawn[12];
	POINT point[12];

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
			pawn[i] = MEN;
	}	
				
	bool makeMove();

	private:
		void setRedPawns();
		void setWhitePawns();

};



#endif
