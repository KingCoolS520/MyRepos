//
//  T11EventDisp.h
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#ifndef __T0818__T11EventDisp__
#define __T0818__T11EventDisp__

#include "cocos2d.h"
USING_NS_CC;

// 1. 该对话框启用时，游戏暂停
// 2. 该对话框销毁时，游戏继续
// 3. 当改层出现时，除了该层，其他触摸禁止
// 4. 由灰色的透明的遮盖层
class MyModelDlg : public Layer
{
public:
    CREATE_FUNC(MyModelDlg);
    
    Menu* _menu;
    EventListenerTouchOneByOne* _ev2;
    
    bool init()
    {
        Layer::init();
        
        // 透明的遮罩层
        LayerColor* layer = LayerColor::create(Color4B::GRAY);
        addChild(layer);
        layer->setOpacity(128);
        
        
        Menu* menu = Menu::create();
        _menu = menu;
        addChild(menu);
        
        MenuItem* item = MenuItemFont::create("OK", [&](Ref*)
        {
            this->removeFromParent();
        });
        menu->addChild(item);
        
        auto ev = EventListenerTouchOneByOne::create();
        _ev2 = ev;
        ev->onTouchBegan = CC_CALLBACK_2(Menu::onTouchBegan, _menu);
        ev->onTouchMoved = CC_CALLBACK_2(Menu::onTouchMoved, _menu);
        ev->onTouchEnded = CC_CALLBACK_2(Menu::onTouchEnded, _menu);
        ev->onTouchCancelled = CC_CALLBACK_2(Menu::onTouchCancelled, _menu);
        
        ev->setSwallowTouches(true);
        _eventDispatcher->addEventListenerWithFixedPriority(ev, -101);

        
        return true;
    }
    
    EventListenerTouchOneByOne* _ev;
    void onEnter()
    {
        auto ev = EventListenerTouchOneByOne::create();
        _ev = ev;
        ev->onTouchBegan = [](Touch*, Event*){return true;};
        ev->setSwallowTouches(true);
        _eventDispatcher->addEventListenerWithFixedPriority(ev, -100);
        
        Director::getInstance()->pause();
        Layer::onEnter();
    }
    void onExit()
    {
        _eventDispatcher->removeEventListener(_ev);
        _eventDispatcher->removeEventListener(_ev2);
        Director::getInstance()->resume();
        Layer::onExit();
    }
};

class T11EventDisp : public Layer
{
public:
    CREATE_FUNC(T11EventDisp);
    
    bool init();
    Sprite* _sprite;
    
    EventListenerTouchOneByOne* _ev;
    
    int firstTouchId = 0;
    int secondTouchId = 0;
    
    int jumpPressId = 0;
    int movePressId = 0;
    
    float _distPrev;
    
    
    void onExit()
    {
    //    this->_eventDispatcher->removeEventListener(_ev);
        Layer::onExit();
    }
};

#endif /* defined(__T0818__T11EventDisp__) */
