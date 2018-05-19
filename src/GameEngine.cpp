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
	ENDGAME endGame = NOT_END;
	do{
		do{
			showWindow();
			if(activePlayer->playertype == MAN) {  
				if(!makeMove(activePlayer))
					return QUIT;
			} else 
				AI::makeMove(Board, activePlayer);
		}while(Board.playerHasNextBeating());
	
		if(RULES::makeKings(Board))
			refreshSprites();

		if(activePlayer == playerOne) 
			activePlayer = playerTwo;
		else 
			activePlayer = playerOne;
	endGame = RULES::ifEND(Board);
	}while(endGame == NOT_END);	
	
	switch(endGame) {
		case RED_WIN:
			break;
		case DRAW:
			break;
		case WHITE_WIN:
			break;
		default:
			throw ERR_WHO_WINS;
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

