#include "../inc/GameEngine.h"

bool GameEngine::playersSetted = false;

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

	std::cout << "fp: " << fP 
			<< "\tsP: " << sP << "\n" ;

	if((fP=='H' || fP=='h') && (sP=='c' || sP=='C')) {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(AI, WHITE);
		AIplayer.set(WHITE);
		std::cout << "FP: M\n";
	} else if((sP=='H' || sP=='h') && (fP=='c' || fP=='C')) {
		playerOne = new Player(AI, RED);
		playerTwo = new Player(MAN, WHITE);
		AIplayer.set(RED);
		std::cout << "FP: AI\n";
	} else if((fP=='H' || fP=='h') && (sP=='h' || sP=='H')) {
		playerOne = new Player(MAN, RED);
		playerTwo = new Player(MAN, WHITE);
		std::cout << "FP: M SP: M\n";
	} 
		activePlayer = playerOne;	
		playersSetted = true;
}


int GameEngine::play() {
	ENDGAME endGame = NOT_END;
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



