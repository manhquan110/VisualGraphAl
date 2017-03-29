//
//  VisualManager.hpp
//  VisualGraphAl
//
//  Created by mq on 3/29/17.
//
//

#ifndef VisualManager_hpp
#define VisualManager_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "VisualScene.hpp"
enum class ALG{
	ASTAR,
	BFS
};
enum class HEURISTIC{
	MANHATTAN,
	EUCLIDEAN
};
class VisualManager{
	VisualData* data_;
	ALG algorithm_type_;
	HEURISTIC algorithm_heu_type_;
	Sprite* result_path_;
	void DrawLine();
public:
	VisualManager(){
		algorithm_type_ = ALG::ASTAR;
		algorithm_heu_type_ = HEURISTIC::MANHATTAN;
		result_path_ = nullptr;
	};
	VisualManager(VisualData*& matrix);
	void SetConfig(ALG algorithm_type, HEURISTIC heuristic_type = HEURISTIC::MANHATTAN);
	void Start();
	void Refresh();
	void ClearWall();
};

#endif /* VisualManager_hpp */
