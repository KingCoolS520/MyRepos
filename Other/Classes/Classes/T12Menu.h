//
//  T12Menu.h
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#ifndef __T0818__T12Menu__
#define __T0818__T12Menu__

#include "cocos2d.h"
USING_NS_CC;


class MyMenu2 : public Menu
{
public:
    CREATE_FUNC(MyMenu2);
    bool init()
    {
        Menu::init();
        
        scheduleUpdate();
        return true;
    }
    
    void update(float dt)
    {
        this->retain();
        if(_selectedItem && _state == Menu::State::TRACKING_TOUCH)
        {
            _selectedItem->activate();
        }
        this->release();
    }
};

class MyMenu : public Menu
{
public:
    CREATE_FUNC(MyMenu);
    bool init()
    {
        Menu::init();
        return true;
    }
    
    bool onTouchBegan(Touch* touch, Event*)
    {
        if (_state != Menu::State::WAITING || ! _visible || !_enabled)
        {
            return false;
        }
        
        for (Node *c = this->_parent; c != nullptr; c = c->getParent())
        {
            if (c->isVisible() == false)
            {
                return false;
            }
        }
        
        _selectedItem = this->getItemForTouch(touch);
        if (_selectedItem)
        {
            _state = Menu::State::TRACKING_TOUCH;
            _selectedItem->selected();
            _selectedItem->activate();
            return true;
        }
        
        return false;
    }
    
    void onTouchEnded(Touch*, Event*)
    {
        CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchEnded] -- invalid state");
        this->retain();
        if (_selectedItem)
        {
            _selectedItem->unselected();
        }
        _state = Menu::State::WAITING;
        this->release();
    }
};



class T12Menu: public Layer
{
public:
    CREATE_FUNC(T12Menu);
    bool init();
};

#endif /* defined(__T0818__T12Menu__) */
