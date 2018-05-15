#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH
#include <iostream>
#include "Player.h"

enum ERROR_CODE { SUC_OK, ERR_CREATE_PLAYERS=201 };


class GameEngine {
	
	GameEngine():playerOne(nullptr), playerTwo(nullptr), 
			     activePlayer(nullptr) {
				 }

	Player* playerOne;
	Player* playerTwo;
	Player* activePlayer;

	void createPlayers(PLAYERTYPE, PLAYERTYPE);

	public:

	static GameEngine& Game() {
		static GameEngine game;
		return game;
	}

	int play() {
		try{
			createPlayers(MAN, AI);
		}catch(ERROR_CODE e){
			std::cout << "cannot create players: " << e << "\n";
		}
		// wylosuj zawodnika
		// wyrenderuj okno 
		// while(true){
		// ruch aktywnego gracza
		// odswiez okno
		// }
		return SUC_OK;
	}
		
	~GameEngine() {
		delete playerOne;
		delete playerTwo;
		delete activePlayer;
	}

};


#endif
