//
//  T11EventDisp.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#include "T11EventDisp.h"


bool T11EventDisp::init()
{
    Layer::init();
    
    // 事件派发器是一个单例
    EventDispatcher* evDisp = Director::getInstance()->getEventDispatcher();
    if(evDisp == _eventDispatcher)
    {
        CCLOG("equal");
    }
    else
    {
        CCLOG("not equal");
    }
#if 0
    _sprite = Sprite::create();
    addChild(_sprite);
    
    // 注册事件
    
    // 固有优先级是0
    // 如果有多个节点注册了相同触摸事件，那么按照ZOrder来处理优先级
    // 被注册的监听器，会随着节点的删除而注销
  //  evDisp->addEventListenerWithSceneGraphPriority(
    
    {
        auto ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [&](Touch*, Event*){
            CCLOG("touch began1");
            this->removeFromParent();
            return true;};
        
        evDisp->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    
    // 固有优先级由参数指定
    // 如果注册了多个监听器，那么固有优先级越小越优先
    // 被注册的监听器，必须手动释放
    // 常常不用。。。。
  //  evDisp->addEventListenerWithFixedPriority()
    {
        auto ev = EventListenerTouchOneByOne::create();
        _ev = ev;
        
        
        ev->onTouchBegan = [=](Touch*, Event*)
        {
            CCLOG("touch began2");
            int data = 50;
            evDisp->dispatchCustomEvent("event1", &data);
            
            return true;
        };
        evDisp->addEventListenerWithFixedPriority(ev, -1);
    }
    
    // 注册自定义事件
    {
        auto func = [](EventCustom* ev){
            int* p = (int*)ev->getUserData();
            CCLOG("Custom event %d", *p);
        };
        evDisp->addCustomEventListener("event1",func);
    }
#endif
    
#if 0
    Layer* layer = Layer::create();
    addChild(layer);
    layer->setLocalZOrder(-1);
    
    {
        auto ev = EventListenerTouchOneByOne::create();
        ev->setSwallowTouches(true);
        ev->onTouchBegan = [&](Touch*, Event*)
        {
            CCLOG("touch began1");
            return true;
        };
        
        evDisp->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    {
        auto ev = EventListenerTouchOneByOne::create();
        ev->setSwallowTouches(true);
        ev->onTouchBegan = [&](Touch*, Event*){
            CCLOG("touch began2");
            return true;};
        
        evDisp->addEventListenerWithSceneGraphPriority(ev, layer);
    }
#endif
    
#if 0
    // 1. 注册一个触摸处理来处理多点的单点触摸
    // 2. 注册多个触摸处理
    {
        auto ev = EventListenerTouchOneByOne::create();
        
        ev->onTouchBegan = [&](Touch* touch, Event*)
        {
            
            if(this->firstTouchId == 0)
            {
                this->firstTouchId = touch->getID();
            }
            else if(this->secondTouchId == 0)
            {
                this->secondTouchId = touch->getID();
            }
            else // 第三个手指
            {
                return false;
            }
            return true;
        };
        
        ev->onTouchMoved = [&](Touch*touch, Event*)
        {
            if(touch->getID() == firstTouchId)
            {
                // 左手在移动
            }
            else if(touch->getID() == secondTouchId)
            {
                // 右手在移动
            }
        };
        
        ev->onTouchEnded = [&](Touch* touch, Event*)
        {
            if(touch->getID() == firstTouchId) firstTouchId = 0;
            if(touch->getID() == secondTouchId) secondTouchId = 0;
        };
        
        evDisp->addEventListenerWithSceneGraphPriority(ev, this);
    }
#endif
    
#if 0
    // 模态对话框：UI的概念
    auto winSize = Director::getInstance()->getWinSize();
    Sprite* bg = Sprite::create("Images/background3.jpg");
    addChild(bg);
    bg->setPosition(winSize.width/2, winSize.height/2);
    
    // 解析plist文件，并且把大图中的小图作为精灵帧加入到缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/grossini_blue.plist");
    
    // 把精灵帧从缓存中获取，并加入到数组
    Vector<SpriteFrame*> frames;
    for(int i=0; i<4; ++i)
    {
        char name[256];
        sprintf(name, "grossini_blue_%02d.png", i+1);
        
        SpriteFrameCache* cache = SpriteFrameCache::getInstance();
        SpriteFrame* frame = cache->getSpriteFrameByName(name);
        frames.pushBack(frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(0.1f);
    
    Animate* animate2 = Animate::create(animation);
    Sprite* sprite2 = Sprite::create();
    sprite2->runAction(RepeatForever::create(animate2));
    addChild(sprite2);
    sprite2->setPosition(200, 200);
    
    
    {
        auto ev = EventListenerTouchOneByOne::create();
        
        ev->onTouchBegan = [&](Touch*, Event*)
        {
            MyModelDlg* dlg = MyModelDlg::create();
            addChild(dlg);
            return true;
        };
        
        evDisp->addEventListenerWithSceneGraphPriority(ev, this);
    }
#endif
    
#if 0
    // 多点触摸
    auto ev = EventListenerTouchAllAtOnce::create();
    ev->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event *event)
    {
        int count = (int)touches.size();
        if(count != 2)
            return;
        Vec2 pt1 = touches[0]->getLocation();
        Vec2 pt2 = touches[1]->getLocation();
        _distPrev = pt1.getDistance(pt2);
        // 不要返回值的，多点触碰是不需要返回值的
    };
    ev->onTouchesEnded =[&](const std::vector<Touch*>& touches, Event *event)
    {
        int count = (int)touches.size();
        if(count != 2)
            return;
        
        Vec2 pt1 = touches[0]->getLocation();
        Vec2 pt2 = touches[1]->getLocation();
        float distNow = pt1.getDistance(pt2);
        
        
        // 缩放图片的效果
            float dt = distNow - _distPrev;
            
            Rect rc = _sprite->getBoundingBox();
            
            float scale = (rc.size.width + dt) / (rc.size.width);
            
            _sprite->setScale(_sprite->getScale()*scale);
       
        
        
    };

      ev->onTouchesMoved=[](const std::vector<Touch*>& touches, Event *event)
    {
        int count = (int)touches.size();
        if(count != 2)
            return;
    };

  //  ev->onTouchesCancelled;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif
    
#if 1
    // 键盘监听演示
    auto ev = EventListenerKeyboard::create();
    ev->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* unused_event)
    {
        // 试一下，在windows下，如果按住q不放，会不会持续输出调试信息
        if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
            CCLOG("q is pressed");
        }
    };
    ev->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* unused_event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
            CCLOG("q is relesed");
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif
    
    {
    auto ev = EventListenerAcceleration::create(
    [](Acceleration* acc ,Event*)
    {
        CCLOG("acc.x=%g, acc.y=%g, acc.z=%g, acc.ts=%g",
              acc->x, acc->y, acc->z, acc->timestamp);
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    return true;
}