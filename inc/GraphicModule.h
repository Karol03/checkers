#ifndef GRAPHICMODULE_H
#define GRAPHICMODULE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Board.h"

class Graphic {

	protected:
	sf::RenderWindow *window;
	sf::Texture *board_texture;
	sf::Texture *red_men;
	sf::Texture *white_men;
	sf::Event event;
	sf::Sprite board;
	sf::Sprite pawn[24];
	BOARD Board;

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

	void showWindow() {
			window->clear();
      		window->draw(board);
			drawPawns();
			window->display();
	}


	private:

	void drawPawns() {
		int red=0;
		int white=12;
		for(int x=0; x<8; x++)
			for(int y=0; y<8; y++) {
				if(Board.get(x,y).type!=NONE && Board.get(x,y).type!=FREE) {
					if(Board.get(x,y).color == RED) {
						pawn[red].setPosition(Board.get(x,y).xPos,
							  				  Board.get(x,y).yPos);
						window->draw(pawn[red]);
						red++;
					} else {
						pawn[white].setPosition(Board.get(x,y).xPos,
							  			 		Board.get(x,y).yPos);
						window->draw(pawn[white]);
						white++;
					}
				}
			}
	}

	void setPawnsSprite() {
		for(int i=0; i<12; i++)
			pawn[i].setTexture(*red_men);

		for(int i=12; i<24; i++) 
			pawn[i].setTexture(*white_men);	
	}


	protected:

	bool makeMove(Player* activePlayer) {
		PAWN* activePawn = new PAWN;
		bool pawnSetted = false;
		int Xcoo, Ycoo;
		bool moveDone = false;

		while(!moveDone){
			while(window->pollEvent(event)) {
				if(event.type == sf::Event::Closed) {
					window->close();
					return false;
				}

				if(event.type == sf::Event::MouseButtonPressed) {
					if(event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mousePos = window->mapPixelToCoords(
										sf::Mouse::getPosition(*window));
						Xcoo = int(mousePos.x)/124;
						Ycoo = int(mousePos.y)/124;
						if(activePlayer->color == Board.get(Xcoo,Ycoo).color) {
								*activePawn = Board.set(Xcoo,Ycoo);
							pawnSetted = true;
						} else if(pawnSetted) {
							int oldX = activePawn->xCoord;
							int oldY = activePawn->yCoord;
							moveDone = Board.move(oldX, oldY, Xcoo,Ycoo);
						}
					}
				}
			}
		}
		
		std::cout << "END Move \n";		
		return true;
	}
};






#endif
