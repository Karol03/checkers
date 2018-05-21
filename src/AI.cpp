#include "../inc/AI.h"	
#include <iostream>


void AIPlayer::makeMove(BOARD& board) { 
	AIMoves bestMove;
   	bestMove = minmaxForBestMove(board, AIcolor, DEPTH);
	bestMove.calculateBestMove(board, AIcolor);
	std::cout << "   |BEST MOVE INFOi| \n"
			<< "s: " << bestMove.score << " | x: " 
			<< bestMove.x << " | y: " << bestMove.y 
			<< " | newX: " << bestMove.newX 
			<< " | newY: " << bestMove.newY << "\n";
	board.move(bestMove.x, bestMove.y, bestMove.newX, bestMove.newY);
}


AIMoves AIPlayer::minmaxForBestMove(BOARD& board, COLOR color, 
									int depth, bool isMax) {
	
	if(depth<=0 || board.countPlayersPawns(RED)==0 ||
					board.countPlayersPawns(WHITE)==0) { 
		color = opositeColor(color);
		AIMoves myMove;
		myMove.board = board;
		myMove.score = estimateResult(board);
		return myMove;
	}
	
	if(isMax)
		return max(board, color, depth);
	else 
		return min(board, color, depth);

}


int AIPlayer::estimateResult(BOARD& board) {	
	int WP = 0;
	int RP = 0;
	switch(RULES::ifEND(board)) {
		case WHITE_WIN:
			if(AIcolor == WHITE)
				return 50;
			else
				return -50;
		
		case RED_WIN:
			if(AIcolor == RED)
				return 50;
			else
				return -50;
				
		case DRAW:
			return 0;

		case NOT_END:
			WP = board.countPlayersMENS(WHITE)*1+
					board.countPlayersKINGS(WHITE)*5;
			RP = board.countPlayersMENS(RED)*1+
					board.countPlayersKINGS(RED)*5;
			if(AIcolor == WHITE)
				return WP-RP;
			else
				return RP-WP;		

		default:
			throw 209;
	}
}

AIMoves AIPlayer::max(BOARD board, COLOR color, int depth) {
	std::vector<AIMoves> allMoves;
	bool isBeat = false;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if(board.get(i,j).color == color) {		
				possibleMoves(board, board.set(i,j), allMoves, isBeat);
			   	for(AIMoves& nextMove : allMoves) { 
					nextMove = minmaxForBestMove(nextMove.board,			
												opositeColor(color),
												--depth, false);	
				} 
			}
	return getMaxMoves(allMoves);
}

AIMoves AIPlayer::min(BOARD board, COLOR color, int depth) {
	std::vector<AIMoves> allMoves;
	bool isBeat = false;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			if(board.get(i,j).color == color) {		
				possibleMoves(board, board.set(i,j), allMoves, isBeat);
			   	for(AIMoves& nextMove : allMoves) { 
					nextMove = minmaxForBestMove(nextMove.board,			
												opositeColor(color),
												--depth, false);	
				} 
			}
	return getMinMoves(allMoves);
}

int AIPlayer::possibleMoves(const BOARD& board, const PAWN& pawn,
								std::vector<AIMoves>& newBoards,
								bool& isBeat) {
	int allMoves = 0;
	if(pawn.type == MEN) {
			if(isBeat) {
				std::cout << "ONLY BEAT\n";
				return (allMoves = allBeating(board, pawn, newBoards));
			}else {
				if((allMoves = allBeating(board, pawn, newBoards))) {
					isBeat = true;
					std::cout << "isBeat = true;\n";
					return allMoves;
				}
				std::cout << "normal moves\n";
				return allNormalMoves(board, pawn, newBoards);
			}
	} else if(pawn.type == KING) {
		// if king
		return allMoves;
	}
	throw 305;
}

int AIPlayer::allNormalMoves(const BOARD& board, const PAWN& pawn,
								std::vector<AIMoves>& moves) {
	int allMoves = 0;
	if(pawn.color == RED) {
		if(moveDL(board, pawn, moves)) ++allMoves;
		if(moveDR(board, pawn, moves)) ++allMoves;
		return allMoves;
	} else if(pawn.color == WHITE) {
		if(moveUL(board, pawn, moves)) ++allMoves;
		if(moveUR(board, pawn, moves)) ++allMoves;
		return allMoves;	
	}
	return allMoves;
}
	
int AIPlayer::allBeating(const BOARD& board, const PAWN& pawn,
						std::vector<AIMoves>& beats) {
	int allMoves = 0;
	if(jumpUL(board, pawn, beats)) {
		++allMoves; 
	}
	if(jumpUR(board, pawn, beats)) ++allMoves;
	if(jumpDL(board, pawn, beats)) ++allMoves;
	if(jumpDR(board, pawn, beats)) ++allMoves;
	return allMoves;	
}

bool AIPlayer::moveUL(BOARD board, const PAWN& pawn, 
				std::vector<AIMoves>& moves) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	if(pawn.type == MEN) {
		if(x-1>=0 && y-1>=0) {
			if(board.get(x-1,y-1).type == FREE) {
				board.set(x-1,y-1) = pawn;
				board.set(x,y).erase();
				moves.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isMove = false;
		for(int i=1; x-i>=0 && y-i>=0; i++)
			if(board.get(x-i,y-i).type == FREE) {
				moves.push_back(AIMoves(moveToXY(board, x, y, x-i, y-i)));
				isMove = true;
			} else
				return isMove;
	}
	throw 311;
}
	
bool AIPlayer::moveUR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& moves) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	if(pawn.type == MEN) {
		if(x+1<8 && y-1>=0) {
			if(board.get(x+1,y-1).type == FREE) {
				board.set(x+1,y-1) = pawn;
				board.set(x,y).erase();
				moves.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isMove = false;
		for(int i=1; x+1<8 && y-i>=0; i++)
			if(board.get(x+i,y-i).type == FREE) {
				moves.push_back(AIMoves(moveToXY(board, x, y, x+i, y-i)));
				isMove = true;
			} else 	
				return isMove;
	}
	throw 311;
}
	
bool AIPlayer::moveDL(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& moves) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	if(pawn.type == MEN) {
		if(x-1>=0 && y+1<8) {
			if(board.get(x-1,y+1).type == FREE) {
				board.set(x-1,y+1) = pawn;
				board.set(x,y).erase();
				moves.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
		return false;
	} else if(pawn.type == KING) {
		bool isMove = false;
		for(int i=1; x-i>=0 && y+i<8; i++)
			if(board.get(x-i,y+i).type == FREE) {
				moves.push_back(AIMoves(moveToXY(board, x, y, x-i, y+i)));
				isMove = true;
			} else
				return isMove;
	}
	throw 311;
}
	
bool AIPlayer::moveDR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& moves) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	if(pawn.type == MEN) {
		if(x+1<8 && y+1<8) {
			if(board.get(x+1,y+1).type == FREE) {
				board.set(x+1,y+1) = pawn;
				board.set(x,y).erase();
				moves.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isMove = false;
		for(int i=1; x+i<8 && y+i<8; i++)
			if(board.get(x+i,y+i).type == FREE) {
				moves.push_back(AIMoves(moveToXY(board, x, y, x+i, y+i)));
				isMove = true;
			} else
				return isMove;
	}
	throw 311;
}

bool AIPlayer::jumpUL(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	int enemyX;
	int enemyY;
	if(pawn.type == MEN) {
		if(x-2>=0 && y-2>=0) {
			if(board.get(x-2, y-2).type==FREE &&
				board.get(x-1, y-1).color==opositeColor(pawn.color)) {
				board.set(x-2, y-2) = pawn;
				board.set(x, y).erase();
				board.set(x-1, y-1).erase();
				beats.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isEnemy = false;
		for(int i=1; x-i>=0 && y-i>=0; i++) {
			if(board.get(x-i,y-i).type != FREE) {
				if(board.get(x-i,y-i).color != pawn.color)
					return false;
				else {
					if(isEnemy)
						return false;
					isEnemy = true;
					enemyX = x-i;
					enemyY = y-i;
				}
			} else {
				if(isEnemy) {
					board.set(x-i, y-i) = pawn;
					board.set(x, y).erase();
					board.set(enemyX, enemyY).erase();
					beats.push_back(AIMoves(board));
					return true;
				}
			}
		}
		return false;
	}
	throw 312;
}
	
bool AIPlayer::jumpUR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	int enemyX;
	int enemyY;
	if(pawn.type == MEN) {
		if(x+2<8 && y-2>=0) {
			if(board.get(x+2, y-2).type==FREE &&
				board.get(x+1, y-1).color==opositeColor(pawn.color)) {
				board.set(x+2, y-2) = pawn;
				board.set(x, y).erase();
				board.set(x+1, y-1).erase();
				beats.push_back(AIMoves(board));
				std::cout << "JUMP UR\n";
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {	
		bool isEnemy = false;
		for(int i=1; x+i<8 && y-i>=0; i++) {
			if(board.get(x+i,y-i).type != FREE) {
				if(board.get(x+i,y-i).color != pawn.color)
					return false;
				else {
					if(isEnemy)
						return false;
					isEnemy = true;
					enemyX = x+i;
					enemyY = y-i;
				}
			} else {
				if(isEnemy) {
					board.set(x+i, y-i) = pawn;
					board.set(x, y).erase();
					board.set(enemyX, enemyY).erase();
					beats.push_back(AIMoves(board));
					return true;
				}
			}		
		}
		return false;
	}
	throw 312;
}
	
bool AIPlayer::jumpDL(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	int enemyX;
	int enemyY;
	if(pawn.type == MEN) {
		if(x-2>=0 && y+2<8) {
			if(board.get(x-2, y+2).type==FREE &&
				board.get(x-1, y+1).color==opositeColor(pawn.color)) {
				board.set(x-2, y+2) = pawn;
				board.set(x, y).erase();
				board.set(x-1, y+1).erase();
				beats.push_back(AIMoves(board));
				std::cout << "JUMP DL\n";
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isEnemy = false;
		for(int i=1; x-i>=0 && y+i<8; i++) {
			if(board.get(x-i,y+i).type != FREE) {
				if(board.get(x-i,y+i).color != pawn.color)
					return false;
				else {
					if(isEnemy)
						return false;
					isEnemy = true;
					enemyX = x-i;
					enemyY = y+i;
				}
			} else {
				if(isEnemy) {
					board.set(x-i, y+i) = pawn;
					board.set(x, y).erase();
					board.set(enemyX, enemyY).erase();
					beats.push_back(AIMoves(board));
					return true;
				}
			}
		}
		return false;
	}
	throw 312;
}

bool AIPlayer::jumpDR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats) {
	int x = pawn.xCoord;
	int y = pawn.yCoord;
	int enemyX;
	int enemyY;
	if(pawn.type == MEN) {
		if(x+2<8 && y+2<8) {
			if(board.get(x+2, y+2).type==FREE &&
				board.get(x+1, y+1).color==opositeColor(pawn.color)) {
				board.set(x+2, y+2) = pawn;
				board.set(x, y).erase();
				board.set(x+1, y+1).erase();
				beats.push_back(AIMoves(board));
				return true;
			} else 
				return false;
		} else
			return false;
	} else if(pawn.type == KING) {
		bool isEnemy = false;
		for(int i=1; x+i<8 && y+i<8; i++) {
			if(board.get(x+i,y+i).type != FREE) {
				if(board.get(x+i,y+i).color != pawn.color)
					return false;
				else {
					if(isEnemy)
						return false;
					isEnemy = true;
					enemyX = x+i;
					enemyY = y+i;
				}
			} else {
				if(isEnemy) {
					board.set(x+i, y+i) = pawn;
					board.set(x, y).erase();
					board.set(enemyX, enemyY).erase();
					beats.push_back(AIMoves(board));
					return true;
				}
			}
		}
		
		return false;
	}
	throw 312;
}

AIMoves AIPlayer::getMaxMoves(std::vector<AIMoves> possibleAIMoves) {
	AIMoves best = possibleAIMoves[0];
	for(const AIMoves& move : possibleAIMoves) 
		if(best < move)
			best = move; 
	return best;	
}
	
AIMoves AIPlayer::getMinMoves(std::vector<AIMoves> possibleAIMoves) {
	AIMoves best = possibleAIMoves[0];
	for(const AIMoves& move : possibleAIMoves) 
		if(best > move)
			best = move; 
	return best;	
}
	
COLOR AIPlayer::opositeColor(COLOR color) {
	if(color == RED)
		return WHITE;
	else if(color == WHITE)
		return RED;
	return BLANK;
}
	
BOARD AIPlayer::moveToXY(BOARD board, int x, int y, int newX, int newY) {
	PAWN pawn = board.get(x,y);
	board.set(x,y).erase();
	board.set(newX, newY) = pawn;
	return board;
}

