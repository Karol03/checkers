#include "../inc/GameEngine.h"
#include <unistd.h>

#define WAIT_MOMENT usleep(10000);
#define WAIT_MORE_MOMENT usleep(500000);

bool GameEngine::playersSetted = false;
bool GameEngine::AIvsAI = false;

void GameEngine::createPlayers() {
	if(playerOne || playerTwo || activePlayer)
		throw ERR_CREATE_PLAYERS;


	playerOne = new Player(AI, RED);
	playerTwo = new Player(MAN, WHITE);

	AIplayer.set(RED);
	activePlayer = playerOne;	
}

void GameEngine::setPlayers(char* argv[]) {
	char fP, sP;
	char* fArg = argv[1];
	std::cout << "1, 2: " << fArg[1] << " " << fArg[2] << "\n";	
	if(sizeof(argv[1])/sizeof(char) >= 3) {
		fP = fArg[1];
		sP = fArg[2];
	} else
		return;

	if((fP=='H' || fP=='h') && (sP=='c' || sP=='C')) {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(AI, WHITE);
		AIplayer.set(WHITE);
	} else if((sP=='H' || sP=='h') && (fP=='c' || fP=='C')) {
		playerOne = new Player(AI, RED);
		playerTwo = new Player(MAN, WHITE);
		AIplayer.set(RED);
	} else if((fP=='H' || fP=='h') && (sP=='h' || sP=='H')) {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(MAN, WHITE);
	} else if(fP=='c' && sP=='c') {
		playerOne = new Player(AI, RED);
		playerTwo = new Player(AI, WHITE);
		AIplayer.set(RED);	
		AIsecondplayer.set(WHITE);	
		AIvsAI = true;
	}
		activePlayer = playerOne;	
		playersSetted = true;
}


int GameEngine::play() {
	ENDGAME endGame = NOT_END;
	
	if(AIvsAI) {
		AIfight();
		return QUIT;
	}

	if(!playersSetted)
		createPlayers();

	do{
		do{
			showWindow();
			if(activePlayer->playertype == MAN) {  
				if(!makeMove(activePlayer))
					return QUIT;
			} else 
				AIplayer.makeMove(Board);
		}while(Board.playerHasNextBeating());
		
		if(activePlayer == playerOne) 
			activePlayer = playerTwo;
		else 
			activePlayer = playerOne;
		
		if(RULES::makeKings(Board))
			refreshSprites();

		endGame = RULES::ifEND(Board);
	}while(endGame == NOT_END);	
	
	

	return SUC_OK;
}


void GameEngine::AIfight() {
	ENDGAME endGame = NOT_END;
	bool whoseTurn = true;
	
	do{
		do{
			showWindow();
			if(whoseTurn)
				AIplayer.makeMove(Board);
			else
				AIsecondplayer.makeMove(Board);
			
			WAIT_MOMENT
		}while(Board.playerHasNextBeating());
		
		if(RULES::makeKings(Board))
			refreshSprites();
			
		whoseTurn = !whoseTurn; 

		WAIT_MORE_MOMENT
		endGame = RULES::ifEND(Board);
	}while(endGame == NOT_END);	

}
