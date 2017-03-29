//
//  InitBG.hpp
//  VisualGraphAl
//
//  Created by mq on 3/27/17.
//
//

#ifndef InitBG_hpp
#define InitBG_hpp

#include <stdio.h>

#endif /* InitBG_hpp */

#include <cocos2d.h>
#include <vector>
using namespace cocos2d;

class InitBG{
	TMXTiledMap* init_;
public:
	InitBG();
	TMXTiledMap* GetBG();
	std::vector<Vec2> GetObjCoord();
};
