#ifndef BOARD_HH
#define BOARD_HH
#include "Pawn.h"
#include "Player.h"
#include <iostream>
#include <cmath>

enum MOVE_TYPES { NORMAL=1, BEATING, NOT_ALLOWED };


struct BOARD {
	PAWN coord[8][8];
	
	PAWN get(int x, int y) const {
		return coord[x][y];
	}

	PAWN& set(int x, int y) {
		return coord[x][y];
	}

	BOARD() {
		setNoneAndFreePawns();
		setRedPawns();
		setWhitePawns();
	}
	
	bool move(int oldX, int oldY, int newX, int newY) {
		MOVE_TYPES playerMove = moveAllowed(oldX, oldY, newX, newY);
		
		if(playerHasBeating(oldX, oldY))
			while(playerMove != BEATING)
				playerMove = moveAllowed(oldX, oldY, newX, newY);

		switch(playerMove) {
			case NORMAL:
				coord[newX][newY] = coord[oldX][oldY];
				coord[newX][newY].setCoord(newX, newY);
				coord[oldX][oldY].erase();
				break;
			
			case BEATING:
				coord[newX][newY] = coord[oldX][oldY];
				coord[newX][newY].setCoord(newX, newY);
				coord[oldX][oldY].erase();
				beating(oldX, oldY, newX, newY, coord[newX][newY].color);
				break;

			case NOT_ALLOWED:
				return false;
		}
		
		return true;
	}

	int countPlayersPawns(Player* player) {
		int count = 0;

		for(int x=0; x<8; x++)
			for(int y=0; y<8; y++)
				if(coord[x][y].color == player->color)
					count++;
		return count;
	}


	private:
	
	void printStates() {
		for(int x=0; x<8; x++) {
			for(int y=0; y<8; y++) {
				std::cout << coord[x][y].type << "   ";
			}
			std::cout << "\n";
		}
	}

	void setNoneAndFreePawns() {
		for(int x=0; x<8; x++)
			for(int y=0; y<8; y++) {
				if((y+x)%2) {
					coord[x][y].type = FREE;
					coord[x][y].color = BLANK;
				} else {
					coord[x][y].type = NONE;
					coord[x][y].color = BLANK;
				}
			}
	}	


	void setRedPawns() {
		for(int y=0; y<3; y++)
			for(int x=1; x<8; x+=2) {
				if(y%2) {
					coord[x-1][y].type  = MEN;
					coord[x-1][y].color = RED;
					coord[x-1][y].xCoord = x-1;
					coord[x-1][y].yCoord = y;
					coord[x-1][y].countPawnPosition();
				} else {
					coord[x][y].type = MEN;
					coord[x][y].color = RED;
					coord[x][y].xCoord = x;
					coord[x][y].yCoord = y;
					coord[x][y].countPawnPosition();
				}
			}
	}

	void setWhitePawns() {
		for(int y=5; y<8; y++)
			for(int x=1; x<8; x+=2) {
				if(y%2) {
					coord[x-1][y].type  = MEN;
					coord[x-1][y].color = WHITE;
					coord[x-1][y].xCoord = x-1;
					coord[x-1][y].yCoord = y;
					coord[x-1][y].countPawnPosition();
				} else {
					coord[x][y].type = MEN;
					coord[x][y].color = WHITE;
					coord[x][y].xCoord = x;
					coord[x][y].yCoord = y;
					coord[x][y].countPawnPosition();
				}
			}
	}

	MOVE_TYPES moveAllowed(int oldX, int oldY, int newX, int newY) {
		if(coord[newX][newY].type != FREE)
			return NOT_ALLOWED;
		
		PAWN *activePawn = new PAWN;	
		*activePawn = coord[oldX][oldY];
		if(abs(newX-oldX) == abs(newY-oldY)) {
			if(activePawn->type == MEN) {
				if(menNormalStep(oldY, newY, activePawn->color)) 
					return NORMAL;
				else if(menJump(oldX, oldY, newX, newY, activePawn->color))
					return BEATING;
				else 
					return NOT_ALLOWED;
			} else if(activePawn->type == KING) {
				return kingStep(oldX, oldY, newX, newY);
			}
		}
		return NOT_ALLOWED;
	}
			
	bool menNormalStep(int oldY, int newY, COLOR color) {
		if(color == RED)
			return (newY-1 == oldY ? true : false);
		else
			return (newY+1 == oldY ? true : false);
	}

	bool menJump(int oldX, int oldY, int newX, int newY, COLOR color) {
		if(abs(oldX-newX)!=2 || abs(oldY-newY)!=2 )
			return false;

		if(color == RED) {
			if(oldX > newX) {
				if(oldY > newY) {
					if(coord[oldX-1][oldY-1].color == WHITE)
						return true;
				} else {
					if(coord[oldX-1][oldY+1].color == WHITE)
						return true;
				}
			} else {
				if(oldY > newY) {
					if(coord[oldX+1][oldY-1].color == WHITE)
						return true;
				} else {
					if(coord[oldX+1][oldY+1].color == WHITE)
						return true;
				}
			}
		} else {
			if(oldX > newX) {
				if(oldY > newY) {
					if(coord[oldX-1][oldY-1].color == RED)
						return true;
				} else {
					if(coord[oldX-1][oldY+1].color == RED)
						return true;
				}
			} else {
				if(oldY > newY) {
					if(coord[oldX+1][oldY-1].color == RED)
						return true;
				} else {
					if(coord[oldX+1][oldY+1].color == RED)
						return true;
				}
			}
		}
		return false;
	}


	void beating(int oldX, int oldY, int newX, int newY, COLOR color) { 
		if(color == RED) {
			if(oldX > newX) {
				if(oldY > newY) {
					if(coord[oldX-1][oldY-1].color == WHITE)
						coord[oldX-1][oldY-1].erase(); 	
				} else {
					if(coord[oldX-1][oldY+1].color == WHITE)
						coord[oldX-1][oldY+1].erase();
				}
			} else {
				if(oldY > newY) {
					if(coord[oldX+1][oldY-1].color == WHITE)
						coord[oldX+1][oldY-1].erase();
				} else {
					if(coord[oldX+1][oldY+1].color == WHITE)
						coord[oldX+1][oldY+1].erase();
				}
			}
		} else {
			if(oldX > newX) {
				if(oldY > newY) {
					if(coord[oldX-1][oldY-1].color == RED)
						coord[oldX-1][oldY-1].erase(); 	
				} else {
					if(coord[oldX-1][oldY+1].color == RED)
						coord[oldX-1][oldY+1].erase(); 	
				}
			} else {
				if(oldY > newY) {
					if(coord[oldX+1][oldY-1].color == RED)
						coord[oldX+1][oldY-1].erase(); 	
				} else {
					if(coord[oldX+1][oldY+1].color == RED)
						coord[oldX+1][oldY+1].erase(); 	
				}
			}
		}
		
	}

	MOVE_TYPES kingStep(int oldX, int oldY, int newX, int newY) {
		bool oponentPawn = false;
		int jump = abs(oldX-newX);
		int x,y;

		for(int i=1; i<=jump; i++) {
			if(oldX < newX) {
				if(oldY < newY) {
					if(coord[oldX+i][oldY+i].color == coord[oldX][oldY].color)
						return NOT_ALLOWED;
					else if(!oponentPawn && coord[oldX+i][oldY+i].type!=FREE){
						oponentPawn = true;
						x = oldX+i;
						y = oldY+i;
					}
				} else {
					if(coord[oldX+i][oldY-i].color == coord[oldX][oldY].color)
						return NOT_ALLOWED;
					else if(!oponentPawn && coord[oldX+i][oldY-i].type!=FREE){
						oponentPawn = true;
						x = oldX+i;
						y = oldY-i;	
					}
				}
			} else {
				if(oldY < newY) {
					if(coord[oldX-i][oldY+i].color == coord[oldX][oldY].color)
						return NOT_ALLOWED;
					else if(!oponentPawn && coord[oldX-i][oldY+i].type!=FREE){
						oponentPawn = true;
						x = oldX-i;
						y = oldY+i;
					}
				} else {
					if(coord[oldX-i][oldY-i].color == coord[oldX][oldY].color)
						return NOT_ALLOWED;
					else if(!oponentPawn && coord[oldX-i][oldY-i].type!=FREE){
						oponentPawn = true;
						x = oldX-i;
						y = oldY-i;
					} 
				}
			}
		}
		
		if(!oponentPawn)
			return NORMAL;
		else {
			coord[x][y].erase();
			return BEATING;
		}

		return NOT_ALLOWED;
	}


	bool playerHasBeating(int x, int y) {
		

		return false;
	}
};




#endif
