//
//  Algorithm.cpp
//  VisualGraphAl
//
//  Created by mq on 3/28/17.
//
//

#include "Algorithm.hpp"

float fScoreManhattan(Piece* x, Piece* y){
	float hScore = fabsf(x->getPosition().x - y->getPosition().x) + fabsf(x->getPosition().y - y->getPosition().y);
	return (x->getGScore() + hScore);
}
float fScoreEuclidean(Piece* x, Piece* y){
	//This evaluate the Euclidean heuristic score
	float hScore = sqrt(pow(x->getPosition().x - y->getPosition().x, 2) + pow(x->getPosition().y - y->getPosition().y, 2));
	return (x->getGScore()+ hScore);
}
int lowfScoreManhattan(std::vector<Piece*>& input, Piece* Goal){
	int lowestIter = 0;
	Piece* lowest = input[0];
	for (int i = 0; i < input.size(); i++)
	{
		if (fScoreManhattan(lowest, Goal) > fScoreManhattan(input[i], Goal))
		{
			lowest = input[i];
			lowestIter = i;
		}
	}
	return lowestIter;
}
int lowfScoreEuclidean(std::vector<Piece*>& input, Piece* Goal){
	int lowestIter = 0;
	Piece* lowest = input[0];
	for (int i = 0; i < input.size(); i++)
	{
		if (fScoreEuclidean(lowest, Goal) > fScoreEuclidean(input[i], Goal))
		{
			lowest = input[i];
			lowestIter = i;
		}
	}
	return lowestIter;
}
Piece* getSpriteFromPosition(std::vector<Piece*>& input, Vec2 Position)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i]->getPosition() == Position)
		{
			return input[i];
		}
	}
	return nullptr;
}

Sprite* AStar::Run(){
	std::vector<Piece*> openSet;
	std::vector<Piece*> closeSet;
	Piece* current;

	openSet.push_back(start_);
	
	while (!openSet.empty())
	{
		int currentIter;
		
		if (heuristic_ == HEURISTIC::MANHATTAN)
				currentIter = lowfScoreManhattan(openSet, goal_);
		else
			currentIter = lowfScoreEuclidean(openSet, goal_);
		
		current = openSet[currentIter];
		if (current->getPosition() == goal_->getPosition())
		{
			return current;
		}
		openSet.erase(openSet.begin() + currentIter);
		closeSet.push_back(current);
		
		//Neighbors
		Vec2 Up(0, 32);
		Vec2 Down(0, -32);
		Vec2 Left(-32, 0);
		Vec2 Right(32, 0);
		Vec2 UL(-32, 32);
		Vec2 UR(32, 32);
		Vec2 DL(-32, -32);
		Vec2 DR(32, -32);
		std::vector<Piece*> Neighbors;
		//Add 4 Neighbors of current in vector input into Neighbors
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + Up));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + Down));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + Left));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + Right));
		
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + UL));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + UR));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + DL));
		Neighbors.push_back(getSpriteFromPosition(input_, current->getPosition() + DR));
		for (int i = 0; i < Neighbors.size(); ++i)
		{
			if (Neighbors[i] == nullptr || Neighbors[i]->getType() == TYPE::WALL)
				continue;
			Neighbors[i]->setBrowser();
			//If a Neighbor is in closeSet
			if (getSpriteFromPosition(closeSet, Neighbors[i]->getPosition()) != NULL)
			{
				continue;  //Already evaluated
			}
			//Increase gScore by 1
			float newGScore = current->getGScore() + 1;
			//If a Neightbor is not in openSet
			if (getSpriteFromPosition(openSet, Neighbors[i]->getPosition()) == NULL)
			{
				openSet.push_back(Neighbors[i]);
			}
			else if (newGScore >= Neighbors[i]->getGScore())
			{
				continue;  //Not a better path to go on
			}
			//Update Sprite info
			Neighbors[i]->setFather(current);
			Neighbors[i]->setScore(newGScore);
		}
	}
	return nullptr;
}
void AStar::SetConfig(std::vector<Sprite*>& input, Sprite* start, Sprite* end){
	for (auto& i: input)
		input_.push_back(dynamic_cast<Piece*>(i));
	start_ = dynamic_cast<Piece*>(start);
	goal_ = dynamic_cast<Piece*>(end);
}
void AStar::SetHeuristic(HEURISTIC heu){
	heuristic_ = heu;
}
