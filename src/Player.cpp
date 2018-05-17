#include "../inc/Player.h"

 
bool Player::makeMove(Player* oponent) {
	if(playertype == MAN) {
		MANmakeMove();
		// sprawdz czy gracz moze wykonac ruch - jesli nie zwroc true
		// jezeli tak pozwol graczowi wykonac ruch	
		return false;
	} else 
		AImakeMove();
		
	return false; 
}

void Player::AImakeMove() {






}

void Player::MANmakeMove() {





}
