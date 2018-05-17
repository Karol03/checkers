#ifndef PLAYER_HH
#define PLAYER_HH
#include "Pawn.h"

enum PLAYERTYPE { MAN=1, AI };

class Player {

	public:
	const PLAYERTYPE playertype;
	const COLOR color;

	Player(PLAYERTYPE playertype, COLOR color): playertype(playertype)
	   										  , color(color) {
											  }			

	private:
};



#endif
