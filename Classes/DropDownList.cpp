//
//  DropDownList.cpp
//  CustomDropDownList
//
//  Created by ESoragoto on 11/20/14.
//
//


#include "cocos2d.h"
#include "DropDownList.h"

USING_NS_CC;

NS_CC_BEGIN

namespace CustomDropDownListBox {
    DropDownList::DropDownList(Label *label,
                               Size show_label_size,
                               Size main_menu_cell_size) :
    show_label_(label),
    is_need_show_menu_(false),
    last_selected_index_(0)
    {
        show_label_size_ = show_label_size;
        main_menu_cell_size_ = main_menu_cell_size;
        
        main_menu_ = Menu::create();
//        main_menu_->setPosition(Point(show_label_size_.width / 2,
//                                      show_label_size_.height / 2));
        CustomSetPosition(main_menu_,
                    Point(0,
                          0));
        main_menu_->setColor(kDropDownListNormalColor3B);
		main_menu_->setOpacity(90);
        main_menu_->retain();
        
//        show_label_->setPosition(Point(show_label_size_.width / 2,
//                                       show_label_size_.height / 2));
        CustomSetPosition(show_label_,
                    Point(0,
                          0));
//        show_label_->setColor(kDropDownListNormalColor3B);
		show_label_->setColor(kColorWhite);
        
        this->addChild(show_label_);
        
        this->setContentSize(show_label_size_);
    }//DropDownList::DropDownList
    
    DropDownList::~DropDownList() {};
    
    void DropDownList::OpenListener()
    {
        //添加触摸监听
        listener_touch_ = EventListenerTouchOneByOne::create();
        listener_touch_->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan, this);
        listener_touch_->onTouchEnded = CC_CALLBACK_2(DropDownList::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_touch_, this);
        //输出启动监听的信息
        log("listener ready");
    }//DropDownList::OpenListener
    
    DropDownList *DropDownList::Create(Label *label,
                                       Size show_label_size,
                                       Size main_menu_cell_size)
    {
        auto *list = new DropDownList(label,
                                      show_label_size,
                                      main_menu_cell_size);
        list->autorelease();
        return list;
    }//*DropDownList::create
    
    std::string DropDownList::GetString()
    {
        return show_label_->getString();
    }//DropDownList::GetString
    
    int DropDownList::GetSelectedIndex()
    {
        return last_selected_index_;
    }//DropDownList::GetSelectedIndex
    
    void DropDownList::SetSelectedIndex(int index)
    {
        last_selected_index_ = index;//获取被选中对象的index参数
        
        //遍历所有元素
        for (int i = 0, j = (int)select_labels_.size(); i < j; i++)
        {
            //根据index的值判断是否是被选中的对象
            if ( last_selected_index_ == i)
            {//如果是被选中的对象，则设置其背景色为被选中的颜色，并且传回该对象的string值(显示的内容)
                bg_layers_[i]->setColor(kColorWhite);
                show_label_->setString(select_labels_[i]->getString());
            }
            else
            {//如果不是被选中的对象，则设置嘁背景色为普通颜色
                bg_layers_[i]->setColor(kColorWhite);
            }
        }
    }//DropDownList::SetSelectedIndex
        
    bool DropDownList::onTouchBegan(Touch *touch,
                                  Event *event)
    {
        //获取点击位置
        auto location_in_view = touch->getLocationInView();
        auto location = Director::getInstance()->convertToGL(location_in_view);
        
        //控制台输出被点击的位置
//        log("BEGAN----------");
//        log("location: %f, %f",
//            location.x,
//            location.y);
		
        //判断菜单是否需要显示
        if (false == is_need_show_menu_)
        {//菜单不需要显示的场合
            Rect show_rect;
            show_rect.origin = this->getPosition();//获取显示区的Position
            show_rect.size = show_label_size_;//获取显示区的Size
            
            //输出到控制台
//            log("rect----------");
//            log("location: %f, %f",
//                show_rect.origin.x,
//                show_rect.origin.y);
//            log("size: %f, %f",
//                show_rect.size.width,
//                show_rect.size.height);
			
            //判断触摸点的Position是否在显示区内
            if (show_rect.containsPoint(location))
            {//点击位置在显示区内的场合，即需要显示菜单
                is_need_show_menu_ = true;//设置状态为需要显示菜单
                return true;
            }
        }
        else
        {//菜单需要显示的场合(包含可能已经显示了菜单的状态)
            Rect list_rect;
            list_rect.origin = this->getPosition();
            list_rect.size = show_label_size_;
            
            //判断触摸点的Position是否在显示区外
            if (!list_rect.containsPoint(location))
            {//点击位置不在显示区内的场合
                OnClose();//关闭main_menu_
            }
        }
        
        return false;
    }//DropDownList::onTouchBegan
    
    void DropDownList::onTouchEnded(cocos2d::Touch *touch,
                                    cocos2d::Event *event)
    {
        //判断是否需要显示菜单
        if (true == is_need_show_menu_)
        {
            //遍历元素以上色
            for (int i = 0, j = (int)select_labels_.size(); i < j; i++)
            {
                //判断出上一次选择的对象
                if (last_selected_index_ == i)
                {//当前元素是上次选中的对象的场合
                    bg_layers_[i]->setColor(kColorWhite);//上色高亮
                }
                else
                {//普通元素的场合
                    bg_layers_[i]->setColor(kColorWhite);
                }
            }
            //添加到场景以显示
            addChild(main_menu_);
        }
    }//DropDownList::onTouchEnded
    
    void DropDownList::AddLabel(Label *label)
    {
        auto *normal_color = LayerColor::create(kColorWhile4B,
                                                main_menu_cell_size_.width,
                                                main_menu_cell_size_.height);
        auto *pSelectedColor = LayerColor::create(kColorWhile4B,
                                                  main_menu_cell_size_.width,
                                                  main_menu_cell_size_.height);
        //std::vector::push_back
        bg_layers_.push_back(normal_color);
        select_labels_.push_back(label);
        
        //生成main_menu_的元素
//        auto ite = MenuItemLabel::create(<#cocos2d::Node *label#>, <#const ccMenuCallback &callback#>)
//        MenuItemSprite::Create(<#cocos2d::Label *label#>, <#cocos2d::Size show_label_size#>, <#cocos2d::Size main_menu_cell_size#>)
//        MenuItemSprite::create()
        auto item = MenuItemSprite::create(normal_color,
                                           pSelectedColor,
                                           NULL,
                                           this,
                                           SEL_MenuHandler(&DropDownList::OnSelected));
        
        label->setPosition(Point(main_menu_cell_size_.width / 2,
                                 main_menu_cell_size_.height / 2));
        item->addChild(label);
        //select_labels_是向量，select_labels_.size()表示其包含元素的个数
        item->setTag((int)select_labels_.size() - 1);
        item->setPosition(0,
                          - (int)select_labels_.size() * main_menu_cell_size_.height);
        main_menu_->addChild(item);
    }//DropDownList::AddLabel
    
    void DropDownList::OnSelected(Ref *sender)
    {
        auto item = dynamic_cast<MenuItem *>(sender);
        
        if (item)
        {
            last_selected_index_ = item->getTag();
            show_label_->setString(select_labels_[item->getTag()]->getString());
        }
        OnClose();
    }//DropDownList::OnSelected
    
    void DropDownList::OnClose()
    {
        removeChild(main_menu_,
                    true);
        is_need_show_menu_ = false;
    }//DropDownList::OnClose
    
    //手动写Position设置方法……不想改锚点
    void DropDownList::CustomSetPosition(Node *node,
                                   Point point)
    {
        node->setPosition(Point(point.x + show_label_size_.width / 2,
                                point.y + show_label_size_.height / 2));
    }//DropDownList::CustomSetPosition
}//namespace CustomDropDownListBox

NS_CC_END
