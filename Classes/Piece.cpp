//
//  Piece.cpp
//  VisualGraphAl
//
//  Created by mq on 3/27/17.
//
//

#include "Piece.hpp"

Piece* Piece::create(TYPE type){
	auto ret = new (std::nothrow) Piece(type);
	if(ret) {
		ret->schedule(schedule_selector(Piece::update));
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}
Piece::Piece(TYPE type){
	initWithFile("map32.png");
	this->setAnchorPoint(Vec2(0.5, 0.5));
	browser_ = false;
	type_ = type;
	overlapping_ = false;
	father_ = nullptr;
	gscore_ = 0;
	draw_ = false;
	if (type_ == TYPE::START){
		this->setColor(Color3B::GREEN);
	} else if (type_ == TYPE::END){
		this->setColor(Color3B::RED);
	}
	// add touch event
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();
		
		if(rect.containsPoint(p))
		{
			return true; // to indicate that we have consumed it.
		}
		
		return false; // we did not consume this event, pass thru.
	};
	listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		CCLOG("move swallow %d", this);
		if (type_ == TYPE::START || type_ == TYPE::END){
			auto mouse = touch->getLocation();
			int x = round(float(mouse.x) / 16);
			int y = round(float(mouse.y) / 16);
			if (x > 0 && y > 0){
				if (x % 2 == 0){
					++x;
				}
				if (y % 2 == 0){
					++y;
				}
				this->setPosition(x*16, y*16);
				auto begin = ScaleTo::create(0.03f, 1.15f, 1.15f);
				auto end = ScaleTo::create(0.07f, 1.0f, 1.0f);
				this->runAction(Sequence::create(begin, end, NULL));
			}
		}
		
	};
	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if (touch->getLocation().distance(this->getPosition()) <= 22){
    		auto begin = ScaleTo::create(0.03f, 1.15f, 1.15f);
    		auto end = ScaleTo::create(0.2f, 1.0f, 1.0f);
    		this->runAction(Sequence::create(begin, end, NULL));
    		CCLOG("touched MySprite");
		
		
    		if (type_ == TYPE::NONE){
				this->setColor(Color3B('\xff','\xff','\xff'));
    			this->setColor(Color3B(179, 179, 179));
    			type_ = TYPE::WALL;
    		} else if (type_ == TYPE::WALL){
				ClearWall();
    		}
		}
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
void Piece::update(float dt){
	if (this->getPosition().distance(Matrix->end->getPosition()) == 0.0f){
		if (!overlapping_){
			overlapping_ = true;
			CCLOG("over lapping");
		}
	} else if (overlapping_){
        overlapping_ = false;
        CCLOG("not lapping");
    }
	if (browser_ && this->getColor() != Color3B::GREEN && !draw_){
		this->setColor(Color3B(99, 255, 242));
	}
}
bool Piece::isOverLapping(){
    return overlapping_;
}
TYPE Piece::getType(){
    return type_;
}
float Piece::getGScore(){
	return gscore_;
}
void Piece::setFather(Sprite* father){
	father_ = father;
}
void Piece::setScore(float score){
	gscore_ = score;
}
void Piece::Refresh(){
	browser_ = false;
	gscore_ = 0;
	father_ = nullptr;
	draw_ = false;
	if (type_ == TYPE::NONE){
		this->setColor(Color3B('\xff','\xff','\xff'));
	}
}
void Piece::ClearWall(){
	if (type_ == TYPE::WALL){
		type_ = TYPE::NONE;
		this->setColor(Color3B('\xff','\xff','\xff'));
	}
	Refresh();
}
void Piece::Draw(){
	if (type_ != TYPE::START || type_ != TYPE::END){
		this->setColor(Color3B::YELLOW);
		draw_ = true;
	}
}
void Piece::setBrowser(){
	if(!(type_ == TYPE::START) && !(type_ == TYPE::END))
		browser_ = true;
}
Piece* Piece::getFather(){
	return dynamic_cast<Piece*>(father_);
}
