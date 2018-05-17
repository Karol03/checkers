#ifndef RULES_HH
#define RULES_HH
#include "Board.h"
#include "Pawn.h"

enum WAY_TO_END { NOT_END, LOSE=1, DRAW=50, WIN=100 };

class RULES {
	
	public:
		static WAY_TO_END ifAnyMoves(BOARD& board, Player* player,
									Player* oponent) {
			bool opWitMov = false;
			if(board.countPlayersPawns(player) == 0)
				return LOSE;
			else if(board.countPlayersPawns(oponent) == 0)
				return WIN;
			
			opWitMov = withoutMoves(board, oponent);
			if(withoutMoves(board, player)) {
				if(opWitMov)
					return DRAW;
				else
					return LOSE;
			} else if(opWitMov)
				return WIN;
			return NOT_END;
		}


	private:
		static bool withoutMoves(BOARD& board, Player* player) {
			PAWN* activePawn = new PAWN;
			for(int x=0; x<8; x++)
				for(int y=0; y<8; y++) {
					*activePawn = board.set(x,y); 
					if(activePawn->color == player->color)
						if(moveUL(board, activePawn) || 
						   moveUR(board, activePawn) ||
						   moveDR(board, activePawn) ||
						   moveDL(board, activePawn) )
								return false;
				}
			return true;
		}

		
		static bool moveUL(BOARD& board, PAWN* pawn) {
			int tmp = 1;
			for(int x=pawn->xCoord-1, y=pawn->yCoord-1; 
					x>=0 && y>=0 && tmp<2; x--, y--, tmp++)
				if(board.get(x,y).type == FREE)
				return true;
			return false;
		}
		
		static bool moveUR(BOARD& board, PAWN* pawn) {
			int tmp = 1;
			for(int x=pawn->xCoord+1, y=pawn->yCoord-1; 
					x<8 && y>=0 && tmp<2; x++, y--, tmp++)
				if(board.get(x,y).type == FREE)
				return true;
			return false;
		}
		
		static bool moveDL(BOARD& board, PAWN* pawn) {
			int tmp = 1;
			for(int x=pawn->xCoord-1, y=pawn->yCoord+1; 
					x>=0 && y<8 && tmp<2; x--, y++, tmp++)
				if(board.get(x,y).type == FREE)
				return true;
			return false;
		}
		
		static bool moveDR(BOARD& board, PAWN* pawn) {
			int tmp = 1;
			for(int x=pawn->xCoord+1, y=pawn->yCoord+1; 
					x<8 && y<8 && tmp<2; x++, y++, tmp++)
				if(board.get(x,y).type == FREE)
				return true;	
			return false;
		}

};






#endif
