#ifndef GRAPHICMODULE_H
#define GRAPHICMODULE_H
#include <SFML/Graphics.hpp>


class Graphic {

	protected:
	sf::RenderWindow *window;
	sf::Texture *board_texture;
	sf::Texture *red_men;
	sf::Texture *white_men;
	sf::Sprite board;

	Graphic() {
		window = new sf::RenderWindow(sf::VideoMode(1000,1000), "Checkers");
		board_texture = new sf::Texture();
		board_texture->loadFromFile("images/board.png");
		board.setTexture(*board_texture);
	}

	bool showWindow() {
        sf::Event event;
        window->pollEvent(event);
		if (event.type == sf::Event::Closed){
			window->close();
        	return false;
		}
		window->clear();
      	window->draw(board);
		window->display();
    	return true;
	}



	~Graphic() {
		delete white_men;
		delete red_men;
		delete board_texture;
		delete window;
	}	



};






#endif
