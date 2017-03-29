//
//  VisualScene.cpp
//  VisualGraphAl
//
//  Created by mq on 3/21/17.
//
//

#include "VisualScene.hpp"
#include "SimpleAudioEngine.h"
#include "InitBG.hpp"
#include "Piece.hpp"

#include <ui/CocosGUI.h>
#include "VisualManager.hpp"
USING_NS_CC;

VisualData* Matrix = new VisualData;
VisualManager Manager(Matrix);

Scene* VisualScene::createScene()
{
	auto scene = Scene::create();
	auto layer = VisualScene::create();
	scene->addChild(layer);
	
	return scene;
}

// on "init" you need to initialize your instance
bool VisualScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(VisualScene::menuCloseCallback, this));
	
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	this->setAnchorPoint(Vec2(0.5, 0.5));
	
	
	InitMap();
	InitMenu();
	return true;
}
void VisualScene::InitMap(){
	InitBG map;
	auto bg = map.GetBG();
	this->addChild(bg, 0);
	auto coordinate = map.GetObjCoord();
	
	auto start = Piece::create(TYPE::START);
	start->setPosition(coordinate[0]);
	this->addChild(start, 1);
	
	auto end = Piece::create(TYPE::END);
	end->setPosition(coordinate[1]);
	this->addChild(end, 1);
	Matrix->end = end;
	Matrix->start = start;
	for (auto i: coordinate){
		auto piece = Piece::create(TYPE::NONE);
		piece->setPosition(i);
		this->addChild(piece);
		Matrix->matrix.push_back(piece);
		piece->retain();
	}
}
void VisualScene::InitMenu(){
    auto visibleSize = Director::getInstance()->getVisibleSize();

	auto menu_layer = LayerColor::create(Color4B::BLACK);
	menu_layer->setOpacity(100);
	menu_layer->setContentSize(Size(200, 200));
	menu_layer->setPosition(700 + 10, visibleSize.height*1.5/3 + 10);
	
	auto label = Label::createWithTTF("Select Algorithm", "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0,0));
	label->setPosition(0, 200 + 10);
	menu_layer->addChild(label);
	
	auto labell = Label::createWithTTF("make a choice", "fonts/Marker Felt.ttf", 24);
	auto box_size = Size(menu_layer->getContentSize());

    list_box_ = CustomDropDownListBox::DropDownList::Create(labell, box_size, Size(box_size.width, 20));
	auto label1 = Label::createWithTTF("A*", "fonts/arial.ttf", 24);

	list_box_->AddLabel(label1);
	list_box_->setPosition(menu_layer->getPosition() - Vec2(0, 0));
 
	this->addChild(list_box_, 3);
	this->addChild(menu_layer, 2);
	list_box_->OpenListener();

	///////////////////////////
	auto label_sub = Label::createWithTTF("choose heuristic", "fonts/arial.ttf", 20);
	auto box_size_sub = Size(list_box_->getContentSize());
	list_box_heuristic_ = CustomDropDownListBox::DropDownList::Create(label_sub, box_size_sub, Size(box_size_sub.width, 20));
	auto label1_sub = Label::createWithTTF("Manhattan", "fonts/arial.ttf", 20);
	
	auto label2_sub = Label::createWithTTF("Euclidean", "fonts/arial.ttf", 20);
	list_box_heuristic_->AddLabel(label1_sub);
	list_box_heuristic_->AddLabel(label2_sub);
	list_box_heuristic_->setPosition(list_box_->getPosition()-Vec2(0, 50));
	this->addChild(list_box_heuristic_, 3);
	list_box_heuristic_->OpenListener();
//	list_box_heuristic_->setVisible(false);
	///////////////////////////
    auto ground_menu_layer = LayerColor::create(Color4B::BLACK);
    ground_menu_layer->setOpacity(130);
    ground_menu_layer->setContentSize(menu_layer->getContentSize() + Size(20, 60));
	ground_menu_layer->setPosition(700, visibleSize.height*1.5/3);
    this->addChild(ground_menu_layer, 1);
	
    auto button_layer = LayerColor::create(Color4B::BLACK);
    button_layer->setOpacity(130);
	button_layer->setPosition(ground_menu_layer->getPosition()-Vec2(0, 100));
	button_layer->setContentSize(ground_menu_layer->getContentSize()-Size(0, 200 - 10));
	this->addChild(button_layer);
	
	auto button_start = ui::Button::create("start.png");
	button_start->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
			case ui::Widget::TouchEventType::ENDED:
			{
				CCLOG("%d", list_box_->GetSelectedIndex());
				switch (list_box_->GetSelectedIndex()) {
					case 0:
						switch (list_box_heuristic_->GetSelectedIndex()) {
							case 0:
								Manager.SetConfig(ALG::ASTAR, HEURISTIC::MANHATTAN);
								break;
							case 1:
								Manager.SetConfig(ALG::ASTAR, HEURISTIC::EUCLIDEAN);
								break;
						}
						break;
				}
				Manager.Start();
			}
				break;
			default:
				break;
		}
			
		});
	auto button_clearwall = ui::Button::create("clear.png");
	button_clearwall->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
			case ui::Widget::TouchEventType::ENDED:
			{
				Manager.ClearWall();
			}
				break;
			default:
				break;
		}
		
	});
	button_layer->addChild(button_start);
	button_layer->addChild(button_clearwall);
	button_start->setPosition(Vec2(button_start->getContentSize().width/5, button_start->getContentSize().height/6));
	button_start->setAnchorPoint(Vec2(0,0));
	button_clearwall->setAnchorPoint(Vec2(0,0));
	button_clearwall->setPosition(button_start->getPosition()+Vec2(button_start->getContentSize().width*1.3, 0));
	
	this->schedule(schedule_selector(VisualScene::update));
}
void VisualScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
	
	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
	
	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
	
	
}
void VisualScene::update(float dt){
//	if (list_box_->GetSelectedIndex() == 0){
//		list_box_heuristic_->setVisible(true);
//	} else if (list_box_heuristic_->isVisible()){
//		list_box_heuristic_->setVisible(false);
//	}
}
