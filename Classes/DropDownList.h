//
//  DropDownList.h
//  CustomDropDownList
//
//  Created by ESoragoto on 11/20/14.
//
//

#ifndef __CustomDropDownList__DropDownList__
#define __CustomDropDownList__DropDownList__

#pragma once

#include <cocos2d.h>

USING_NS_CC;
NS_CC_BEGIN

namespace CustomDropDownListBox
{
    const auto kDropDownListNormalColor4B = Color4B(128,
                                                    128,
                                                    128,
                                                    255);
    const auto kDropDownListSelectedColor4B = Color4B(200,
                                                      200,
                                                      200,
                                                      255);
    const auto kDropDownListHighlightColor4B = Color4B(0,
                                                       0,
                                                       255,
                                                       255);
    const auto kDropDownListNormalColor3B = Color3B(229,
                                                    227,
                                                    227);
    const auto kDropDownListSelectedColor3B = Color3B(200,
                                                      200,
                                                      200);
    const auto kDropDownListHighlightColor3B = Color3B(0,
                                                       0,
                                                       225);
    const auto kColorWhite = Color3B(255,
                                     255,
                                     255);
	const auto kColorWhile4B = Color4B(255,
									   255,
									   255,
									   255);
    class DropDownList : public Layer
    {
    public:
        DropDownList(Label *label,
                     Size show_label_size,
                     Size main_menu_cell_size);
        ~DropDownList();
        
        ///<summary>
        ///初始化
        ///</summary>
        void OpenListener();
        
        ///<summary>
        ///创建实例对象
        ///</summary>
        ///<parm name = "*label">添加一个label作为默认显示</parm>
        ///<parm name = "size">默认尺寸</parm>
        static DropDownList * Create(Label *label,
                                     Size show_label_size,
                                     Size main_menu_cell_size);
        
        ///<summary>
        ///获取选中对象的string
        ///</summary>
        std::string GetString();
        
        ///<summary>
        ///获取选中的index
        ///</summary>
        int GetSelectedIndex();
        
        ///<summary>
        ///设置选中的对象
        ///</summary>
        ///<parm name = "index">对象的index值</parm>
        void SetSelectedIndex(int index);
        
        ///<summary>
        ///开始触摸
        ///</summary>
        ///<parm name = "*touch">触摸对象</parm>
        ///<parm name = "*event">触摸事件</parm>
        virtual bool onTouchBegan(Touch *touch,
                                  Event *event);
        
        ///<summary>
        ///结束触摸
        ///</summary>
        ///<parm name = "*touch">触摸对象</parm>
        ///<parm name = "*event">触摸事件</parm>
        void onTouchEnded(Touch *touch,
                          Event *event);
        
        ///<summary>
        ///添加新的Label以冒充下拉菜单
        ///</summary>
        ///<parm name = "*label">冒充菜单用的label素材</parm>
        void AddLabel(Label *label);
        
        ///<summary>
        ///下拉列表中的项被选中
        ///</summary>
        ///<parm name = "*sender">被点击的的对象</parm>
        void OnSelected(Ref *sender);
        
        ///<summary>
        ///关闭下拉列表
        ///</summary>
        void OnClose();
        
        ///<summary>
        ///自定义的位置设置
        ///</summary>
        ///<parm name = "*sender">被点击的的对象</parm>
        void CustomSetPosition(Node *node,
                               Point point);
        
    private:
        Menu *main_menu_;    //下拉选项列表的集合
        Label *show_label_;   //对显示区用label
        std::vector<Label *> select_labels_;   //用来冒充下拉列表的label们
        std::vector<LayerColor *> bg_layers_; //用于设置背景颜色
        bool is_need_show_menu_; //是否已显示了下拉列表
        int last_selected_index_;  //选中下拉列表的index
        Size main_menu_cell_size_;   //菜单包含项的Size
        Size show_label_size_;  //对显示区用label的占地面积
    
        EventListenerTouchOneByOne *listener_touch_;
    };//class DropDownList : public Layer
}//namespace CustomDropDownListBox
NS_CC_END

#endif //#define __CustomDropDownList__DropDownList__
