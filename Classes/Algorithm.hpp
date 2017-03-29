//
//  Algorithm.hpp
//  VisualGraphAl
//
//  Created by mq on 3/28/17.
//
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "VisualManager.hpp"
float fScoreManhattan(Piece* x, Piece* y);
float fScoreEuclidean(Piece* x, Piece* y);
int lowfScoreManhattan(std::vector<Piece*>& input, Piece* Goal);
int lowfScoreEuclidean(std::vector<Piece*>& input, Piece* Goal);
class AStar{

public:
	AStar(){
		start_ = nullptr;
		goal_ = nullptr;
		heuristic_ = HEURISTIC::MANHATTAN;
	};
	void SetConfig(std::vector<Sprite*>& input, Sprite* start, Sprite* end);
	void SetHeuristic(HEURISTIC heu);
	Sprite* Run();
private:
	HEURISTIC heuristic_;
	std::vector<Piece*> input_;
	Piece* start_;
	Piece* goal_;
};
#endif /* Algorithm_hpp */
