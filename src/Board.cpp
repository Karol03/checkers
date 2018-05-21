#include "../inc/Board.h"
	

	
bool BOARD::move(int oldX, int oldY, int newX, int newY) {
	MOVE_TYPES playerMove = moveAllowed(oldX, oldY, newX, newY);

	switch(playerMove) {
		case NORMAL:
			coord[newX][newY] = coord[oldX][oldY];
			coord[newX][newY].setCoord(newX, newY);
			coord[oldX][oldY].erase();
			xNext = -1;
			yNext = -1;
			break;
			
		case BEATING:
			coord[newX][newY] = coord[oldX][oldY];
			coord[newX][newY].setCoord(newX, newY);
			coord[oldX][oldY].erase();
			if(coord[newX][newY].type == MEN)
				beating(oldX, oldY, newX, newY, coord[newX][newY].color);
			else
				coord[beatCoordX][beatCoordY].erase();
			
			xNext = newX;
			yNext = newY;
			break;
	
		case NOT_ALLOWED:
			return false;
	}	
	return true;
}

int BOARD::countPlayersMENS(COLOR color) {
	int count = 0;

	for(int x=0; x<8; x++)
		for(int y=0; y<8; y++)
			if(coord[x][y].color==color && coord[x][y].type==MEN)
				count++;
	return count;
}

int BOARD::countPlayersKINGS(COLOR color) {
	int count = 0;

	for(int x=0; x<8; x++)
		for(int y=0; y<8; y++)
			if(coord[x][y].color==color && coord[x][y].type==KING)
				count++;
	return count;
}

int BOARD::countPlayersPawns(COLOR color) {
	int count = 0;

	for(int x=0; x<8; x++)
		for(int y=0; y<8; y++)
			if(coord[x][y].color == color)
				count++;
	return count;
}


void BOARD::setNoneAndFreePawns() {
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


void BOARD::setRedPawns() {
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

void BOARD::setWhitePawns() {
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

MOVE_TYPES BOARD::moveAllowed(int oldX, int oldY, int newX, int newY) {
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
			switch(kingStep(oldX, oldY, newX, newY)) {
		   		case NORMAL:
					beatCoordX = -1;
					beatCoordY = -1;
					return NORMAL;
				case NOT_ALLOWED:
					beatCoordX = -1;
					beatCoordY = -1;
					return NORMAL;
				case BEATING:
					return BEATING;
				default:
					beatCoordX = -1;
					beatCoordY = -1;
					return NOT_ALLOWED;
			}
		}
	}
	return NOT_ALLOWED;
}
			
bool BOARD::menNormalStep(int oldY, int newY, COLOR color) {
	if(color == RED)
		return (newY-1 == oldY ? true : false);
	else
		return (newY+1 == oldY ? true : false);
}

bool BOARD::menJump(int oldX, int oldY, int newX, int newY, COLOR color) {
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

void BOARD::beating(int oldX, int oldY, int newX, int newY, COLOR color) { 
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


MOVE_TYPES BOARD::kingMoveUL(int x, int y, int d) {
	bool setOponent = false;
	for(int i=x-1, j=y-1, k=1; i>=0 && j>=0 && k<=d ; i--, j--, k++) {
		if(coord[i][j].color == coord[x][y].color)
			return NOT_ALLOWED;
		else {
			if(coord[i][j].color != BLANK) {
				if(!setOponent) {
					beatCoordX = i;
					beatCoordY = j;
					setOponent = true;
				} else
					return NOT_ALLOWED;
			}
		}
	}
	return BEATING;
}

MOVE_TYPES BOARD::kingMoveUR(int x, int y, int d) {
	bool setOponent = false;
	for(int i=x+1, j=y-1, k=1; i<8 && j>=0 && k<=d ; i++, j--, k++) {
		if(coord[i][j].color == coord[x][y].color)
			return NOT_ALLOWED;
		else {
			if(coord[i][j].color != BLANK) {
				if(!setOponent) {
					beatCoordX = i;
					beatCoordY = j;
					setOponent = true;
				} else
					return NOT_ALLOWED;
			}
		}
	}
	return BEATING;
}

MOVE_TYPES BOARD::kingMoveDL(int x, int y, int d) {
	bool setOponent = false;
	for(int i=x-1, j=y+1, k=1; i>=0 && j<8 && k<=d ; i--, j++, k++) {
		if(coord[i][j].color == coord[x][y].color)
			return NOT_ALLOWED;
		else {
			if(coord[i][j].color != BLANK) {
				if(!setOponent) {
					beatCoordX = i;
					beatCoordY = j;
					setOponent = true;
				} else
					return NOT_ALLOWED;
			}
		}
	}
	return BEATING;
}

MOVE_TYPES BOARD::kingMoveDR(int x, int y, int d) {
	bool setOponent = false;
	for(int i=x+1, j=y+1, k=1; i<8 && j<8 && k<=d ; i++, j++, k++) {
		if(coord[i][j].color == coord[x][y].color)
			return NOT_ALLOWED;
		else {
			if(coord[i][j].color != BLANK) {
				if(!setOponent) {
					beatCoordX = i;
					beatCoordY = j;
					setOponent = true;
				} else
					return NOT_ALLOWED;
			}
		}
	}
	return BEATING;
}

MOVE_TYPES BOARD::kingStep(int oldX, int oldY, int newX, int newY) {
	int distance = abs(oldX-newX);
		
	if(oldX < newX) {
		if(oldY < newY)
			return kingMoveDR(oldX, oldY, distance);		
		else
			return kingMoveUR(oldX, oldY, distance);
	} else {
		if(oldY < newY) 
			return kingMoveDL(oldX, oldY, distance);		
		else
			return kingMoveUL(oldX, oldY, distance);
	}

	throw 205;
}


bool BOARD::playerHasNextBeating() {
	if(beatingFromPosition(xNext, yNext))
		return true;
	xNext = yNext = -1;
	return false;
}

bool BOARD::playerHasBeating(COLOR playerColor) {
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if(coord[i][j].color == playerColor)
				if(beatingFromPosition(i,j))
					return true;
	return false;
}

bool BOARD::ifBeating(int oldX, int oldY, int newX, int newY) {
	if(coord[oldX][oldY].type == MEN) {
		if(menJump(oldX, oldY, newX, newY, coord[oldX][oldY].color))
			return true;
   } else {
		if(kingStep(oldX, oldY, newX, newY) == BEATING)
   			return true;	
   }
	return false;
}


bool BOARD::beatUL(int x, int y, PAWNTYPE PT) {
	bool oponentPawn = false;
	int opX, opY;
	if(PT == MEN) {
		if(x-2>=0 && y-2>=0 && coord[x-2][y-2].type==FREE 
					   && coord[x-1][y-1].color!=BLANK
					   && coord[x][y].color!=coord[x-1][y-1].color)
			return true;
	} else {
		for(int i=x-1, j=y-1; i>=0 && j>=0; i--, j--) {
			if(coord[i][j].color == coord[x][y].color)
				return false;
			else if(coord[i][j].color != BLANK) {
				oponentPawn = true;
				opX = i;
				opY = j;
				break;
			}
		}
	}
	
	if(oponentPawn && opX-1>=0 && opY-1>=0 
					&& coord[opX-1][opY-1].type==FREE) 
		return true;
	
	return false;
}

bool BOARD::beatUR(int x, int y, PAWNTYPE PT) {
	bool oponentPawn = false;
	int opX, opY;
	if(PT == MEN) {
		if(x+2<8 && y-2>=0 && coord[x+2][y-2].type==FREE 
					   && coord[x+1][y-1].color!=BLANK
					   && coord[x][y].color!=coord[x+1][y-1].color)
			return true;
	} else {
		for(int i=x+1, j=y-1; i<8 && j>=0; i++, j--) {
			if(coord[i][j].color == coord[x][y].color)
				return false;
			else if(coord[i][j].color != BLANK) {
				oponentPawn = true;
				opX = i;
				opY = j;
				break;
			}
		}
	}
	if(oponentPawn && opX+1<8 && opY-1>=0 
					&& coord[opX+1][opY-1].type==FREE) 
		return true;
	
	return false;
}

bool BOARD::beatDL(int x, int y, PAWNTYPE PT) {
	bool oponentPawn = false;
	int opX, opY;
	if(PT == MEN) {
		if(x-2>=0 && y+2<8 && coord[x-2][y+2].type==FREE 
					   && coord[x-1][y+1].color!=BLANK
					   && coord[x][y].color!=coord[x-1][y+1].color)
			return true;
	} else {
		for(int i=x-1, j=y+1; i>=0 && j<8; i--, j++) {
			if(coord[i][j].color == coord[x][y].color)
				return false;
			else if(coord[i][j].color != BLANK) {
				oponentPawn = true;	
				opX = i;
				opY = j;
				break;
			}
		}
	}
	if(oponentPawn && opX-1>=0 && opY+1<8 
					&& coord[opX-1][opY+1].type==FREE) 
		return true;

	return false;
}

bool BOARD::beatDR(int x, int y, PAWNTYPE PT) {
	bool oponentPawn = false;
	int opX, opY;
	if(PT == MEN) {
		if(x+2<8 && y+2<8 && coord[x+2][y+2].type==FREE 
					   && coord[x+1][y+1].color!=BLANK
					   && coord[x][y].color!=coord[x+1][y+1].color)
			return true;
	} else {
		for(int i=x+1, j=y+1; i<8 && j<8; i++, j++) {
			if(coord[i][j].color == coord[x][y].color)
				return false;
			else if(coord[i][j].color != BLANK) {
				oponentPawn = true;
				opX = i;
				opY = j;
				break;
			}
		}
	}
	if(oponentPawn && opX+1<8 && opY+1<8 
					&& coord[opX+1][opY+1].type==FREE) 
		return true;
	
	return false;
}

bool BOARD::beatingFromPosition(int x, int y) {
	if(beatUL(x,y,coord[x][y].type) ||
		beatUR(x,y,coord[x][y].type) ||
		beatDL(x,y,coord[x][y].type) ||
		beatDR(x,y,coord[x][y].type))
			return true;
	return false;
}




