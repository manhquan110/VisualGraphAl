//
//  InitBG.cpp
//  VisualGraphAl
//
//  Created by mq on 3/27/17.
//
//

#include "InitBG.hpp"
#include <iostream>
InitBG::InitBG(){
	init_ = TMXTiledMap::create("map32.tmx");
}

TMXTiledMap* InitBG::GetBG(){
	return init_;
}

std::vector<Vec2> InitBG::GetObjCoord(){
	std::vector<Vec2> coordinate;
	for (int x = 0; x < 960; x += 32){
		for (int y = 0; y < 640; y += 32)
			coordinate.push_back(Vec2(x+16, y+16));
	}
	return coordinate;
}
