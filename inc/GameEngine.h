#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH
#include <iostream>
#include "Player.h"
#include "GraphicModule.h"

enum ERROR_CODE { SUC_OK, QUIT, ERR_CREATE_PLAYERS=201 };


class GameEngine : private Graphic {
	
	GameEngine():playerOne(nullptr), playerTwo(nullptr), 
			     activePlayer(nullptr) {
				 }
	
	Player* playerOne;
	Player* playerTwo;
	Player* activePlayer;

	void createPlayers(PLAYERTYPE, PLAYERTYPE);
	void setPlayers();
	void createGameWindow();

	public:
	
	~GameEngine() {
		delete playerOne;
		delete playerTwo;
		delete activePlayer;
	}

	static GameEngine& Game() {
		static GameEngine game;
		return game;
	}

	int setGame();
	int play();	
};


#endif
