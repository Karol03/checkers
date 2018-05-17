#include "../inc/GameEngine.h"

void GameEngine::createPlayers(PLAYERTYPE pt1, PLAYERTYPE pt2) {
	if(playerOne || playerTwo || activePlayer)
		throw ERR_CREATE_PLAYERS;
	playerOne = new Player(pt1, RED);
	playerTwo = new Player(pt2, WHITE);
	activePlayer = playerOne;	
}

int GameEngine::setGame() {
	setPlayers();
	createGameWindow();
	return SUC_OK;
}

int GameEngine::play() {
	bool endGame;
	do{
		if(!showWindow())
			return QUIT;
		
		endGame = activePlayer->makeMove();
		if(activePlayer == playerOne)
			activePlayer = playerTwo;
		else
			activePlayer = playerOne;
	}while(!endGame);
	return SUC_OK;
}

void GameEngine::setPlayers() {
	
	// wyswietl okienko z wyborem graczy
	// utworz graczy na podstawie powyzszego wyboru 
}

void GameEngine::createGameWindow() {
	// stworz okno gry 
	// narysuj szachownice i pionki
}
