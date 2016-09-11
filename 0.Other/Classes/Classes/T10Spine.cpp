//
//  T10Spine.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#include "T10Spine.h"

bool T10Spine::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
    spine::SkeletonAnimation* node = spine::SkeletonAnimation::createWithFile("spine/spineboy.json", "spine/spineboy.atlas");
    addChild(node);
    node->setPosition(winSize.width/2, 0);
    
    /// 让动画动起来
    spTrackEntry*  entry = node->setAnimation(0, "walk", true);
    
    // 设置混合，混合的目的是为了动作切换更加柔和
    node->setMix("shoot", "walk", 0.2f);
    
    // 事件处理
#if 0
    typedef std::function<void(int trackIndex)> StartListener;
    typedef std::function<void(int trackIndex)> EndListener;
    typedef std::function<void(int trackIndex, int loopCount)> CompleteListener;
    typedef std::function<void(int trackIndex, spEvent* event)> EventListener;
#endif
    
#if 0
    spine::EventListener listener = [](int, spEvent* event ){
        CCLOG("event name is %s", event->data->name);
    };
    node->setEventListener(listener);
#endif
    
    
    
    node->setStartListener([](int){
        cocos2d::log("start");
    });
    node->setEventListener([](int, spEvent* event ){
        cocos2d::log("event name is %s", event->data->name);
    });
    
    node->setTimeScale(0.3f);
    node->setDebugBonesEnabled(true);
    node->setRotation(50);
    
   // node->setAttachment("front_bracer", "torso");
    
    
    
    // 发射子弹
    auto ev = EventListenerTouchOneByOne::create();
    
    ev->onTouchBegan = [=](Touch*, Event*){
        // 发射子弹
        node->setAnimation(0, "shoot", false);
        node->addAnimation(0, "walk", true);
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    
    
    
    return true;
}