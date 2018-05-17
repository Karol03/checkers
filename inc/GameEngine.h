#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH
#include <iostream>
#include "Player.h"
#include "GraphicModule.h"

enum ERROR_CODE { SUC_OK, QUIT, ERR_CREATE_PLAYERS=200 };


class GameEngine : private Graphic {
	
	GameEngine():playerOne(nullptr), playerTwo(nullptr), 
			     activePlayer(nullptr) {
		createPlayers(setOponentType(), setPlayerColor());				
	}
	
	Player* playerOne;
	Player* playerTwo;
	Player* activePlayer;

	void createPlayers(PLAYERTYPE, COLOR);
	PLAYERTYPE setOponentType();
	COLOR setPlayerColor();


	public:
	
	~GameEngine() {
		delete playerOne;
		delete playerTwo;
	}

	static GameEngine& Game() {
		static GameEngine game;
		return game;
	}

	int play();	
};


#endif
