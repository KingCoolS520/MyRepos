//
//  T12Menu.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#include "T12Menu.h"

bool T12Menu::init()
{
    Layer::init();
    
#if 0
    MyMenu2* menu = MyMenu2::create();
    addChild(menu);
    
    MenuItemFont* item = MenuItemFont::create("abc");
    menu->addChild(item);
    item->setTag(1);
    MenuItemFont* item1 = MenuItemFont::create("abc");
    menu->addChild(item1);
    item1->setTag(2);
    
    auto callback = [=](Ref* sender){
        
        MenuItem* node = (MenuItem*)sender;
        if(node->getTag() == 1)
        {
            CCLOG("item is clicked");
        }
        else
        {
            CCLOG("item1 is clicked");
        }
    };
    
    item->setCallback(callback);
    item1->setCallback(callback);
    
    // ....
   // item->setPosition(...);
   // item1->setPosition(<#const cocos2d::Vec2 &position#>)
  //  menu->alignItemsHorizontally();
    menu->alignItemsVertically();
#endif
    
    // 一个字符串参数，一个回调函数
    // MenuItemFont::create(, );
    // 三个精灵：Normal， Selected， Disabled
    // MenuItemSprite::create;
    // 三个图片
    // MenuItemImage::create;
    // 使用Label作为参数
    // MenuItemLabel::create(<#cocos2d::Node *label#>);
    
    auto func = [](Ref* sender){
        MenuItemToggle* toggle = (MenuItemToggle*)sender;
        int item = toggle->getSelectedIndex();
        CCLOG("%d", item);
        if(item == 1)
        {
            // 关闭音乐
        }
        else
        {
           
            
        }
    };
    
    MenuItem* item1 = MenuItemFont::create("On");
    MenuItem* item2 = MenuItemFont::create("Off");
    
    MenuItemToggle* toggle = MenuItemToggle::createWithCallback(func, item1, item2, NULL);
    
    Menu* menu = Menu::create();
    menu->addChild(toggle);
    addChild(menu);
    
    
    
    return true;
}