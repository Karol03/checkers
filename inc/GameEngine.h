#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH
#include <iostream>
#include "Player.h"
#include "GraphicModule.h"
#include "Rules.h"
#include "AI.h"

enum ERROR_CODE { SUC_OK, QUIT, ERR_BAD_PLAYER_SETTING = 101,
		ERR_CREATE_PLAYERS=200, ERR_WHO_WINS=300 };


class GameEngine : private Graphic {
	
	GameEngine():playerOne(nullptr), playerTwo(nullptr), 
			     activePlayer(nullptr) {
	}
	
	Player* playerOne;
	Player* playerTwo;
	Player* activePlayer;
	AIPlayer AIplayer;
	static bool playersSetted;
		

	void createPlayers();


	public:
	
	~GameEngine() {
		delete playerOne;
		delete playerTwo;
	}

	static GameEngine& Game() {
		static GameEngine game;
		return game;
	}

	void setPlayers(char* argv[]);

	int play();	
};


#endif
