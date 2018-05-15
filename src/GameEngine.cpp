#include "../inc/GameEngine.h"

void GameEngine::createPlayers(PLAYERTYPE pt1, PLAYERTYPE pt2) {
	if(playerOne || playerTwo || activePlayer)
		throw ERR_CREATE_PLAYERS;
	playerOne = new Player(pt1);
	playerTwo = new Player(pt2);
	activePlayer = playerOne;	

}
