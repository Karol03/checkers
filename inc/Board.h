#ifndef BOARD_HH
#define BOARD_HH
#include "Pawn.h"
#include "Player.h"
#include <cmath>

enum MOVE_TYPES { NORMAL=1, BEATING, NOT_ALLOWED };


struct BOARD {
	PAWN coord[8][8]; 
	int xNext;
	int yNext;
	
	public:
	PAWN get(int x, int y) const {
		return coord[x][y];
	}

	PAWN& set(int x, int y) {
		return coord[x][y];
	}

	BOARD() {
		xNext = yNext = -1;
		beatCoordX = beatCoordY = -1;
		setNoneAndFreePawns();
		setRedPawns();
		setWhitePawns();
	}
	
	bool move(int oldX, int oldY, int newX, int newY);	
	int countPlayersPawns(COLOR color);
	bool playerHasNextBeating();
	bool ifBeating(int oldX,  int oldY, int newX, int newY);
	bool beatingFromPosition(int x, int y);
	bool playerHasBeating(COLOR playerColor);

	private:
	int beatCoordX;
	int beatCoordY;

	void setNoneAndFreePawns();	
	void setRedPawns();
	void setWhitePawns();
	
	MOVE_TYPES moveAllowed(int oldX, int oldY, int newX, int newY);			
	void beating(int oldX, int oldY, int newX, int newY, COLOR color);
	
	bool menNormalStep(int oldY, int newY, COLOR color);
	bool menJump(int oldX, int oldY, int newX, int newY, COLOR color);
	
	bool beatUL(int x, int y, PAWNTYPE PT);
	bool beatUR(int x, int y, PAWNTYPE PT);
	bool beatDL(int x, int y, PAWNTYPE PT);
	bool beatDR(int x, int y, PAWNTYPE PT);

	MOVE_TYPES kingStep(int oldX, int oldY, int newX, int newY); 
	MOVE_TYPES kingMoveUL(int x, int y, int d);
	MOVE_TYPES kingMoveUR(int x, int y, int d);
	MOVE_TYPES kingMoveDL(int x, int y, int d);
	MOVE_TYPES kingMoveDR(int x, int y, int d);
};




#endif
