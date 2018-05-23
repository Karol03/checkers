#ifndef AI_HH
#define AI_HH
#include "Board.h"
#include "Player.h"
#include "Rules.h"
#include "AIMoves.h"
#include <vector>
#include <ctime>

#define DEPTH 5 

class AIPlayer {
	COLOR AIcolor;

	public:	
	void printMove(AIMoves move);  // TO DELETE	
	void bestMoveInfo(AIMoves bestMove);


	void set(COLOR color) { AIcolor = color; }
	void makeMove(BOARD& board);


	AIPlayer() {
		srand(time(NULL));
	}
	private:
	AIMoves minmaxForBestMove(BOARD board, COLOR color, 
							int depth, bool isMax);

	int estimateResult(BOARD board) const;

	AIMoves max(BOARD board, COLOR color, int depth);
	AIMoves min(BOARD board, COLOR color, int depth);


	int possibleMoves(const BOARD& board, const PAWN& pawn,
						std::vector<AIMoves>& moves);

	bool possibleBeats(const BOARD& board, const PAWN& pawn,
						std::vector<AIMoves>& beats);
	
	bool moveUL(BOARD board, const PAWN& pawn, 
				std::vector<AIMoves>& moves);
	
	bool moveUR(BOARD board, const PAWN& pawn, 
				std::vector<AIMoves>& moves);

	bool moveDL(BOARD board, const PAWN& pawn, 
				std::vector<AIMoves>& moves);
	
	bool moveDR(BOARD board, const PAWN& pawn, 
				std::vector<AIMoves>& moves);
	
	bool jumpUL(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats);
	
	bool jumpUR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats); 
	
	bool jumpDL(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats);

	bool jumpDR(BOARD board, const PAWN& pawn,
				std::vector<AIMoves>& beats); 

	AIMoves getMaxMoves(std::vector<AIMoves> possibleAIMoves);	
	AIMoves getMinMoves(std::vector<AIMoves> possibleAIMoves);

	COLOR opositeColor(COLOR color);	

	BOARD moveToXY(BOARD board, int x, int y, int newX, int newY);


};



#endif
