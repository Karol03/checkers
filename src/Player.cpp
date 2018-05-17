#include "../inc/Player.h"


bool Player::makeMove() {
	// sprawdz czy zostaly jakies ruchy - jezeli nie zwroc true
	
	// jezeli czlowiek - wykonaj ruch manualnie przesuwajac pionek
	// sprawdz czy ruch jest dozwolony - jezeli nie powtorz operacje
	
	// jezeli AI - sprawdz drzewo, ktory z ruchow wykonac 
	// wykonaj ruch
	// zwroc false
	return false; 
}

void Player::setRedPawns() {
	int k=0;
	for(int i=0; i<3; i++)
		for(int j=1; j<8; j+=2) {
			point[k].yCoord = i;
			if(i%2)
				point[k].xCoord = j-1;
			else
				point[k].xCoord = j;
			k++;
		}
}

void Player::setWhitePawns() {
	int k=0;
	for(int i=5; i<8; i++)
		for(int j=1; j<8; j+=2) {
			point[k].yCoord = i;
			if(i%2)
				point[k].xCoord = j-1;
			else
				point[k].xCoord = j;
			k++;
		}
}

