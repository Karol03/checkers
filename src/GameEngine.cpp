#include "../inc/GameEngine.h"


void GameEngine::createPlayers(PLAYERTYPE pt, COLOR cl) {
	if(playerOne || playerTwo || activePlayer)
		throw ERR_CREATE_PLAYERS;

	if(cl == RED) {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(MAN, WHITE);
	} else {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(MAN, WHITE);
	}
	activePlayer = playerOne;	
}

int GameEngine::play() {
	bool endGame = false;
	do{
		showWindow();

		if(activePlayer->playertype == MAN) { 
			if(!makeMove(activePlayer))
				return QUIT;
			if(activePlayer == playerOne)
				activePlayer = playerTwo;
			else
				activePlayer = playerOne;
		} else {
			if(activePlayer == playerOne) {
				activePlayer->makeMove(playerTwo);
				activePlayer = playerTwo;
			} else {
				activePlayer->makeMove(playerOne);	
				activePlayer = playerOne;
			}
		}
	}while(!endGame);
	return SUC_OK;
}

PLAYERTYPE GameEngine::setOponentType() {
	// wyswietl okienko z wyborem VS AI lub VS gracz
	// utworz graczy na podstawie powyzszego wyboru 
	return MAN;
}


COLOR GameEngine::setPlayerColor() {
	// wyswietl okno
	// jezeli bialy ustaw bialy
	// jezeli nie ustaw czerwony
	return RED;
}

