#include "../inc/GraphicModule.h"


Graphic::Graphic() {
	window = new sf::RenderWindow(sf::VideoMode(BOARD_SIZE
												,BOARD_SIZE)
									, "Checkers");
	board_texture = new sf::Texture();
	board_texture->loadFromFile(BOARD_TEXTURE);

	red_men = new sf::Texture();
	red_men->loadFromFile(RED_MEN_TEXTURE);

	white_men = new sf::Texture();
	white_men->loadFromFile(WHITE_MEN_TEXTURE);

	red_king = new sf::Texture();
	red_king->loadFromFile(RED_KING_TEXTURE);

	white_king = new sf::Texture();
	white_king->loadFromFile(WHITE_KING_TEXTURE);

	board.setTexture(*board_texture);
	setPawnsSprite();
}
	
Graphic::~Graphic() {
	delete white_men;
	delete red_men;
	delete white_king;
	delete red_king;
	delete board_texture;
	delete window;
}	

void Graphic::showWindow() {
		window->clear();
   		window->draw(board);
		drawPawns();
		window->display();
}


void Graphic::drawPawns() {
	int red=0;
	int white=12;
	refreshSprites();		
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

void Graphic::setPawnsSprite() {
	int red=0;
	int white=12;
	for(int x=0; x<8; x++)
		for(int y=0; y<8; y++)
			if(Board.get(x,y).color == RED) {
				if(Board.get(x,y).type == MEN) {
					pawn[red].setTexture(*red_men);
				} else {
					pawn[red].setTexture(*red_king);
				}
				red++;
			} else if(Board.get(x,y).color == WHITE){
				if(Board.get(x,y).type == MEN) {
					pawn[white].setTexture(*white_men);
				} else {
					pawn[white].setTexture(*white_king);
				}
				white++;
			}
}

bool Graphic::makeMove(Player* activePlayer) {
	PAWN* activePawn = new PAWN;
	bool pawnSetted = false;
	int Xcoo, Ycoo;
	bool moveDone = false;
 	bool nextBeat = false;
	bool mustBeat = false;


	if(Board.xNext!=-1 && Board.yNext!=-1) {
		nextBeat = true;		
		mustBeat = false;
	} else if(Board.playerHasBeating(activePlayer->color)) 
		mustBeat = true;
	
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
					Xcoo = (int(mousePos.x)-73)/MENS_SIZE;
					Ycoo = (int(mousePos.y)-73)/MENS_SIZE;
					if(activePlayer->color 
									== Board.get(Xcoo,Ycoo).color) {
							if(!nextBeat && !mustBeat) {
								*activePawn = Board.set(Xcoo,Ycoo);
								pawnSetted = true;
							} else if(mustBeat) {
						   		if(Board.beatingFromPosition(Xcoo,Ycoo)) {
									*activePawn = Board.set(Xcoo,Ycoo);
									pawnSetted = true;
								}
							} else {
								if(Board.xNext==Xcoo && Board.yNext==Ycoo) {
									*activePawn = Board.set(Xcoo,Ycoo);
									pawnSetted = true;
								}
							}
					} else if(pawnSetted) {
						int oldX = activePawn->xCoord;
						int oldY = activePawn->yCoord;
						if(!nextBeat && !mustBeat) {
							moveDone = Board.move(oldX,oldY,Xcoo,Ycoo);
						} else if(mustBeat) {
							if(Board.ifBeating(oldX, oldY, Xcoo, Ycoo))
								moveDone = Board.move(oldX,oldY,Xcoo,Ycoo);
						} else {
							if(Board.ifBeating(oldX, oldY, Xcoo, Ycoo))
								moveDone = Board.move(oldX,oldY,Xcoo,Ycoo);
						}
					}
				}
			}
		}
	}
	return true;
}
