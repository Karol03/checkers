#include "../inc/GameEngine.h"

#define GAME GameEngine::Game()

int main(int argc, char* argv[]) {
	if(argc == 2)	
		GAME.setPlayers(argv);
	return GAME.play();
}
