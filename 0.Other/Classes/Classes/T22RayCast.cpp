//
//  T22RayCast.cpp
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#include "T22RayCast.h"

void T22RayCast::onEnter()
{
    Layer::onEnter();
    
    auto winSize = Director::getInstance()->getWinSize();
    
    _world = getScene()->getPhysicsWorld();
    _world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _world->setGravity(Vec2(0, 0));
    
    // 标记一头猫
    {
        _cat = Sprite::create("CloseNormal.png");
        addChild(_cat);
        _cat->setPosition(200, 200);
    }
    
    // 很多食物, 食物是刚体
    {
        auto ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [&](Touch* touch, Event*){
            PhysicsBody* body = PhysicsBody::createCircle(20);
            Sprite* sprite = Sprite::create();
            sprite->setPhysicsBody(body);
            sprite->setPosition(touch->getLocation());
            addChild(sprite);
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    // 扫描食物
    /*
        参数1:扫描到刚体之后的回调函数
        参数2:扫描开始点
        参数3:扫描结束点
        参数4:扫描附带参数
     
     _world->rayCast(PhysicsRayCastCallbackFunc func, const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, void *data)
     */
    scheduleUpdate();
    _angle = 0;
    _r = 100;
    _dist = 10000000;
    _food = nullptr;
    _draw= nullptr;
}

bool T22RayCast::rayCastCallback(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)
{
    // info.shape; 食物
    float d =info.shape->getBody()->getNode()->getPosition().getDistance(_cat->getPosition());
    
    if( d<_dist)
    {
        _dist = d;
        _food = info.shape->getBody();
    }
    
    // 表示不关心这个线后面的刚体
    return false;
}

void T22RayCast::update(float)
{
    Vec2 start = _cat->getPosition();
    Vec2 end;  // 跟角度有关系
    end.x = start.x + sinf(CC_DEGREES_TO_RADIANS(_angle)) * _r;
    end.y = start.y + cosf(CC_DEGREES_TO_RADIANS(_angle)) * _r;
    
    if(_draw) _draw->removeFromParent();
    _draw = DrawNode::create();
    addChild(_draw);
    _draw->drawLine(start, end, Color4F::GREEN);
    
    _world->rayCast(CC_CALLBACK_3(T22RayCast::rayCastCallback, this), start, end, nullptr);
    
    _angle += 5;
    if(_angle >= 360)
    {
        /* 吃哪个食物 */
        if(_food)
        {
            _cat->setPosition(_food->getNode()->getPosition());
            _food->getNode()->removeFromParent();
        }
        
        // 恢复参数，准备下一次扫描
        _angle = 0;
        _dist = 10000000;
        _food = nullptr;
    }
}
