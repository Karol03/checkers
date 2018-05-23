#ifndef AIMOVES_HH
#define AIMOVES_HH
#include "Board.h"

struct AIMoves {
	BOARD board;
	int score;
	
	int x, y, newX, newY;
	
	int xCoord;
	int yCoord;

	AIMoves() { 	
		xCoord = yCoord = x = y = newX = newY = -1;	 
		score = 0;
	}

	
	AIMoves(const BOARD& Board) {
		board = Board;
		x = y = newX = newY = -1;	
		score = -99;
	}

	bool operator==(const AIMoves& nextMove) {
		return (score==nextMove.score ? true : false);	}
	
	bool operator<(const AIMoves& nextMove) {
		return score<nextMove.score;	}
	
	bool operator>(const AIMoves& nextMove) {
		return score>nextMove.score;	}

	void set(const AIMoves& prevMove) {
		score = prevMove.score;
	}

	void set(const BOARD& Board) {	board = Board;  }

	int calculateBestMove(const BOARD& prevBoard, COLOR color) {
		for(int i=0; i<8; i++)
			for(int j=0; j<8; j++)
				if(board.get(i,j).type!=FREE && 
								prevBoard.get(i,j).type==FREE) {
					newX = i;
					newY = j;
				} else if(board.get(i,j).type==FREE 
							&& prevBoard.get(i,j).type!=FREE
							&& prevBoard.get(i,j).color==color) {
					x = i;
					y = j;
				}

		if(newX==-1 || newY==-1 || x==-1 || y==-1)
			return 0;
		return 1;
	}


};



#endif
