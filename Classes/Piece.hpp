//
//  Piece.hpp
//  VisualGraphAl
//
//  Created by mq on 3/27/17.
//
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "VisualScene.hpp"
#endif /* Piece_hpp */
using namespace cocos2d;

extern VisualData* Matrix;
enum class TYPE{
	START,
	END,
	WALL,
	NONE
};
class Piece:public Sprite
{
	bool browser_;
	TYPE type_;
	bool overlapping_;
	Piece(TYPE type);
	
	Sprite* father_;
	float gscore_;
	bool draw_;
protected:
	void update(float dt);
public:
	static Piece* create(TYPE type); // create
	void Refresh();
	void ClearWall();
    TYPE getType();
    bool isOverLapping();
	float getGScore();
	void setFather(Sprite* father);
	void setScore(float score);
	Piece* getFather();
	void Draw();
	void setBrowser();
};
