//
//  T21Physics.cpp
//  
//
//  Created by 薛国良 on 15/11/16.
//
//

#include "T21Physics.h"

void T21Physics::onEnter()
{
    Layer::onEnter();
    
    Scene* scene = this->getScene();
    _world = scene->getPhysicsWorld();
    
    _world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   // _world->setGravity(Vec2(0, 0));
    
    {
        PhysicsJointDistance* joint = PhysicsJointDistance::construct(_bodyA, _bodyB, Vec2(0, 0), Vec2(0, 0));
       // PhysicsJointSpring* joint = PhysicsJointSpring::construct(_bodyA, _bodyB, Vec2(0, 0), Vec2(0, 0), 5, 10);
        
        
        _world->addJoint(joint);
        
    }
}

bool T21Physics::init()
{
    Layer::init();
    
    _draw = nullptr;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    {
        PhysicsBody* body = PhysicsBody::createCircle(20, PhysicsMaterial(0.1f, 0.5f, 0.0f) );
    
        Sprite* sprite = Sprite::create();
        addChild(sprite);
        
       // PhysicsShape* shape = body->getShapes().at(0);
       // shape->setRestitution(1.0f);
    
        // 关联
        sprite->setPhysicsBody(body);
    
        sprite->setPosition(winSize.width/4, winSize.height/2);
        
        _bodyA = body;
        
    }
    
    {
       // PhysicsBody* body = PhysicsBody::createCircle(20, PhysicsMaterial(0.1f, 0.5f, 0.0f) );
        
        PhysicsBody* body = PhysicsBody::createEdgeBox(Size(20, 20));
        
        Sprite* sprite = Sprite::create();
        addChild(sprite);
        
        // PhysicsShape* shape = body->getShapes().at(0);
        // shape->setRestitution(1.0f);
        
        // 关联
        sprite->setPhysicsBody(body);
        
        sprite->setPosition(winSize.width/2, winSize.height/2);
        
        _bodyB = body;
    }
    
    {
        PhysicsBody* body = PhysicsBody::createEdgeBox(winSize);
        Sprite* sprite = Sprite::create();
        sprite->setPhysicsBody(body);
        sprite->setPosition(winSize.width/2, winSize.height/2);
        addChild(sprite);
        
      //  PhysicsShape* shape = body->getShapes().at(0);
      //  shape->setRestitution(1.0f);
        
    }
    
    {
#if 0
        _bodyA->setCategoryBitmask(int bitmask); // 0xFFFFFFFF
        _bodyB->setContactTestBitmask();           // 0x0
        
        
        // 是否做碰撞计算
        _bodyA->setCollisionBitmask(int bitmask); // 0xFFFFFFFF
#endif
        
       // _bodyA->setCollisionBitmask(0xFFFFFFFF);
       // _bodyB->setCollisionBitmask(0xFFFFFFFF);
        
        _bodyA->setCategoryBitmask(2);
        _bodyA->setContactTestBitmask(1);
        
        _bodyB->setCategoryBitmask(1);
        _bodyB->setContactTestBitmask(2);
        
        // 碰撞监测
        EventListenerPhysicsContactWithBodies* ev =
        EventListenerPhysicsContactWithBodies::create(_bodyA,
                                                      _bodyB);
        
        ev->onContactBegin =[](PhysicsContact& contact)
        {
            contact.getShapeA()->getBody()->getNode();
            contact.getShapeB();
            CCLOG("Begin");
            
            // 如果返回false，物理引擎对这次碰撞不做碰撞计算
            return false;
        };
        ev->onContactSeperate = [](PhysicsContact& contact){
            CCLOG("End");
        };
#if 0
        ev->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve)
        {
            return true;
        };
        ev->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
        {
            
        };
#endif
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    
    {
        auto ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [&](Touch* touch, Event*){
            
            PhysicsShapeCircle* shape =
            (PhysicsShapeCircle*)_bodyA->getShapes().at(0);
            
            float r = shape->getRadius();
            
            Vec2 pos = touch->getLocation();
            Vec2 pos2 = _bodyA->getNode()->getPosition();
            if(pos.getDistance(pos2) < r)
            {
                return true;
            }
            
            return false;
        };
        
        ev->onTouchMoved = [&](Touch* touch, Event*)
        {
            if(_draw) _draw->removeFromParent();
            
            _draw = DrawNode::create();
            addChild(_draw);
            _draw->drawLine(_bodyA->getNode()->getPosition(), touch->getLocation(), Color4F::GREEN);
        };
        
        ev->onTouchEnded = [&](Touch* touch, Event*){
            if(_draw) _draw->removeFromParent();
            _draw = nullptr;
            
            Vec2 pos = touch->getLocation();
            Vec2 dt = pos - _bodyA->getNode()->getPosition();
            
            _bodyA->setVelocity(dt);
            
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    }
    
    
    
    return true;
}
