#ifndef GRAPHICMODULE_H
#define GRAPHICMODULE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Graphic {

	protected:
	sf::RenderWindow *window;
	sf::Texture *board_texture;
	sf::Texture *red_men;
	sf::Texture *white_men;
	sf::Sprite board;
	sf::Sprite pawn[24];


	Graphic() {
		window = new sf::RenderWindow(sf::VideoMode(1000,1000), "Checkers");
		board_texture = new sf::Texture();
		board_texture->loadFromFile("images/board.png");
		red_men = new sf::Texture();
		red_men->loadFromFile("images/red.png");
		white_men = new sf::Texture();
		white_men->loadFromFile("images/white.png");
		board.setTexture(*board_texture);
		setPawnsSprite();
	}
	
	~Graphic() {
		delete white_men;
		delete red_men;
		delete board_texture;
		delete window;
	}	

	bool showWindow(Player* plOne, Player* plTwo) {
        sf::Event event;
        window->pollEvent(event);
		if(event.type == sf::Event::Closed){
			window->close();
        	return false;
		}

		window->clear();
      	window->draw(board);
		drawPawns(plOne, plTwo);
		window->display();
    	return true;
	}


	private:

	void drawPawns(Player* plOne, Player* plTwo) {
		for(int i=0; i<12; i++) {
			if(plOne->getPawn(i).type != NONE) {
				float x=getPawnPosition(plOne, i, 0);
				float y=getPawnPosition(plOne, i, 1);
				pawn[i].setPosition(x, y);
				window->draw(pawn[i]);
			}
		}

		for(int i=12; i<24; i++) {
			if(plTwo->getPawn(i-12).type != NONE) {
				float x=getPawnPosition(plTwo, i, 0);
				float y=getPawnPosition(plTwo, i, 1);
				pawn[i].setPosition(x, y);
				window->draw(pawn[i]);
			}
		}
	}

	void setPawnsSprite() {
		for(int i=0; i<12; i++)
			pawn[i].setTexture(*red_men);

		for(int i=12; i<24; i++) 
			pawn[i].setTexture(*white_men);	
	}

	float getPawnPosition(Player* player, int number, int coord) {
		if(coord == 0)
			return (float)(player->getPawn(number%12).xCoord*124);
		else
			return (float)(player->getPawn(number%12).yCoord*124);
		return 0.0f;
	}

	protected:

	bool makeMove(Player* activePlayer, Player* oponent) {
        sf::Event event;
		int color;
		PAWN* activePawn = new PAWN;
		bool changePawn = false;

		if(activePlayer->color == RED)
			color = 0;
		else
			color = 1;

		while(activePawn == nullptr || window->isOpen()) {
        	changePawn = true;
			window->pollEvent(event);
			if(event.type == sf::Event::Closed){
				window->close();
        		return false;
			}
			if(event.type == sf::Event::MouseButtonPressed) {
			if(event.mouseButton.button == sf::Mouse::Left || !activePawn) {
				sf::Vector2f mousePos = 
				window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				
				for(int i=color*12; i<12*(color+1); i++) {
					if(pawn[i].getGlobalBounds().contains(mousePos)) {
						*activePawn = activePlayer->getPawn(i%12);
						if(activePawn->type != NONE)
							break;
						activePawn = nullptr;	
					}
				}
			} 
			if(event.mouseButton.button == sf::Mouse::Left || activePawn) {
				sf::Vector2f mousePos = 
				window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				if(activePlayer->color == RED) {
					for(int i=0; i<12; i++) 
						if(pawn[i].getGlobalBounds().contains(mousePos)) 
							if(activePlayer->getPawn(i).type != NONE) {
								*activePawn = activePlayer->getPawn(i);
								break;
							}	
					if(!changePawn)
						break;
					for(int i=12; i<24; i++)
						if(pawn[i].getGlobalBounds().contains(mousePos)) 
							break;
					activePawn->xCoord = int(mousePos.x)%124;
					activePawn->yCoord = int(mousePos.y)%124;
					
				}
			}
		}
		}

				// jezeli myszka jest na obiekcie
				// wybierz obiekt
				// wez pozycje myszki
				// jezeli obiekt wybrany i pole jest dozwolone wykonaj ruch
				// jezeli nacisnieto na inny obiekt zmien obiekt
			
		window->clear();
      	window->draw(board);
		drawPawns(activePlayer, oponent);
		window->display();
			
		return true;
	}
};






#endif
