//
//  VisualScene.hpp
//  VisualGraphAl
//
//  Created by mq on 3/21/17.
//
//

#ifndef VisualScene_hpp
#define VisualScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "DropDownList.h"
struct VisualData{
	std::vector<cocos2d::Sprite*> matrix;
	cocos2d::Sprite* start;
	cocos2d::Sprite* end;
};
extern VisualData* Matrix;
class VisualScene: public cocos2d::Layer
{
	CustomDropDownListBox::DropDownList* list_box_;
	CustomDropDownListBox::DropDownList* list_box_heuristic_;
protected:
	void InitMap();
	void InitMenu();
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(VisualScene);
};
#endif /* VisualScene_hpp */
