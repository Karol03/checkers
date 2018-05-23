#ifndef GRAPHICMODULE_H
#define GRAPHICMODULE_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Board.h"

#define BOARD_TEXTURE "images/board.png"
#define RED_MEN_TEXTURE "images/red.png"
#define RED_KING_TEXTURE "images/red_king.png"
#define WHITE_MEN_TEXTURE "images/white.png"
#define WHITE_KING_TEXTURE "images/white_king.png"
#define BOARD_SIZE 1000
#define MENS_SIZE 124

class Graphic {

	protected:
	sf::RenderWindow *window;
	sf::Texture *board_texture;
	sf::Texture *red_men;
	sf::Texture *white_men;
	sf::Event event;
	sf::Texture *red_king;
	sf::Texture *white_king;
	sf::Sprite board;
	sf::Sprite pawn[24];
	BOARD Board;

	Graphic();
	~Graphic();
		

	void showWindow();
	bool makeMove(Player* activePlayer);
	void refreshSprites() {
		setPawnsSprite(); 
	}

	private:

	void drawPawns();
	void setPawnsSprite();	


	
};






#endif
