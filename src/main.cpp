#include "../inc/GameEngine.h"
#include <iostream>

#define GAME GameEngine::Game()

int main(int argc, char* argv[]) {
	GAME.setGame();
	return GAME.play();
}
