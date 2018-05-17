#include "../inc/Player.h"

 
bool Player::makeMove(Player* oponent) {
	if(!checkIfAnyMoves(oponent))
		return true;

	if(playertype == MAN) {
		MANmakeMove();
		// sprawdz czy gracz moze wykonac ruch - jesli nie zwroc true
		// jezeli tak pozwol graczowi wykonac ruch	
		return false;
	} else 
		AImakeMove();
		
	return false; 
}

void Player::setRedPawns() {
	int k=0;
	for(int i=0; i<3; i++)
		for(int j=1; j<8; j+=2) {
			pawn[k].yCoord = i;
			if(i%2)
				pawn[k].xCoord = j-1;
			else
				pawn[k].xCoord = j;
			pawn[k].type = MEN;
			k++;
		}
}

void Player::setWhitePawns() {
	int k=0;
	for(int i=5; i<8; i++)
		for(int j=1; j<8; j+=2) {
			pawn[k].yCoord = i;
			if(i%2)
				pawn[k].xCoord = j-1;
			else
				pawn[k].xCoord = j;
			pawn[k].type = MEN;
			k++;
		}
}

void Player::AImakeMove() {






}

void Player::MANmakeMove() {





}

bool Player::checkIfAnyMoves(Player* oponent) {
		

	return true;
}


