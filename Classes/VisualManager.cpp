//
//  VisualManager.cpp
//  VisualGraphAl
//
//  Created by mq on 3/29/17.
//
//

#include "VisualManager.hpp"
#include "Algorithm.hpp"

VisualManager::VisualManager(VisualData*& matrix){
	VisualManager();
	data_ = matrix;
}
void VisualManager::Refresh(){
	for (auto& i: data_->matrix){
		dynamic_cast<Piece*>(i)->Refresh();
	}
	dynamic_cast<Piece*>(data_->start)->Refresh();
	dynamic_cast<Piece*>(data_->end)->Refresh();
	result_path_ = nullptr;
}
void VisualManager::ClearWall(){
	for (auto& i: data_->matrix){
		dynamic_cast<Piece*>(i)->ClearWall();
	}
}
void VisualManager::Start(){
	Refresh();
	
	switch (algorithm_type_) {
		case ALG::ASTAR:{
			switch (algorithm_heu_type_) {
				case HEURISTIC::MANHATTAN:
					
					break;
				case HEURISTIC::EUCLIDEAN:
					break;
			}
			AStar A_Star;
			A_Star.SetConfig(data_->matrix, data_->start, data_->end);
			A_Star.SetHeuristic(algorithm_heu_type_);
			result_path_ = A_Star.Run();
			break;
		}
		case ALG::BFS:{
			break;
		}
	}
	DrawLine();
}
void VisualManager::SetConfig(ALG algorithm_type, HEURISTIC heuristic_type){
	algorithm_type_ = algorithm_type;
	algorithm_heu_type_ = heuristic_type;
}
void VisualManager::DrawLine(){
	if (result_path_){
		while (result_path_ != data_->start){
			dynamic_cast<Piece*>(result_path_)->Draw();
			result_path_ = dynamic_cast<Piece*>(result_path_)->getFather();
		}
	}
}
