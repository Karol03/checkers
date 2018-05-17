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
	WAY_TO_END endGame = NOT_END;
	do{
		showWindow();

		if(activePlayer->playertype == MAN) { 
			if(!makeMove(activePlayer))
				return QUIT;
		} else 
			AI::makeMove(Board, activePlayer);

		if(activePlayer == playerOne) {
			endGame = RULES::ifAnyMoves(Board, activePlayer, playerTwo);
			activePlayer = playerTwo;
		} else {
			endGame = RULES::ifAnyMoves(Board, activePlayer, playerOne);
			activePlayer = playerOne;
		}
	std::cout << endGame << "\n";
	}while(endGame == NOT_END);
	
	switch(endGame) {
		case LOSE:
			break;
		case DRAW:
			break;
		case WIN:
			break;
		default:
			break;
	}

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

