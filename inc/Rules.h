#ifndef RULES_HH
#define RULES_HH
#include "Board.h"
#include "Pawn.h"

enum ENDGAME { NOT_END, RED_WIN=1, WHITE_WIN, DRAW };

class RULES {
	
	public:
		static ENDGAME ifEND(BOARD board) {
			if(board.countPlayersPawns(RED) == 0)
				return WHITE_WIN;
			else if(board.countPlayersPawns(WHITE) == 0)
				return RED_WIN;
			else if(withoutMoves(board, RED))
				return WHITE_WIN;
			else if(withoutMoves(board, WHITE))
				return RED_WIN;
					
			return NOT_END;
		}

		static bool makeKings(BOARD& board) {
			int y=0;
			for(int x=0; x<8; x++) 
				if(board.get(x,y).color == WHITE) {
					if(board.get(x,y).type == MEN) {
						board.set(x,y).type = KING;
						return true;
					}
				}
			y=7;
			for(int x=0; x<8; x++) 
				if(board.get(x,y).color == RED) {
					if(board.get(x,y).type == MEN) {
						board.set(x,y).type = KING;
						return true;
					}
				}
			return false;
		}

	private:

		static bool menHasMoves(BOARD& board, PAWN* activePawn) {
			COLOR color = activePawn->color;
			if(color == RED) {
				if(moveDL(board, activePawn) || moveDR(board,activePawn))
					return true;
			} else {
				if(moveUL(board, activePawn) || moveUR(board,activePawn))
					return true;
			}
			return false;
		}	

		static bool kingHasMoves(BOARD& board, PAWN* activePawn) {
			if(moveDL(board, activePawn) || 
				moveDR(board,activePawn) ||
				moveUL(board,activePawn) ||
		   		moveUR(board,activePawn))
				return true;
			
			return false; 
		}

		static bool withoutMoves(BOARD& board, COLOR color) {	
			PAWN* activePawn = new PAWN;		
			for(int x=0; x<8; x++)
				for(int y=0; y<8; y++) {
					*activePawn = board.set(x,y);
					if(activePawn->color == color) {  					
						if(activePawn->type == MEN) { 
							if(menHasMoves(board, activePawn))
								return false;
						} else if(activePawn->type == KING) {
							if(kingHasMoves(board, activePawn))
								return false;
						}
					}
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
