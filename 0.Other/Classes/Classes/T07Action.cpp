//
//  T07Action.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/27.
//
//

#include "T07Action.h"

class MyAction : public ActionInterval
{
public:
    static MyAction* create(float duration, Vec2 center)
    {
        MyAction* ret = new MyAction;
        ret->init(duration, center);
        ret->autorelease();
        return ret;
    }
    
    Vec2 _center;
    Vec2 _origin;
    
    bool init(float duration, Vec2 center)
    {
        ActionInterval::initWithDuration(duration);
        _center = center;
        return true;
    }
    
    virtual void startWithTarget(Node *target)
    {
        ActionInterval::startWithTarget(target);
        _origin = target->getPosition();
    }
    
    // dt: 0 ~ 1表示运动的完成度
    void update(float dt)
    {
#if 0
        float y = _origin.y - _center.y;
        float x = _origin.x - _center.x;
        
        float angle = atan2f(y, x);
#endif
        float r = _origin.getDistance(_center);
        
        Vec2 delta = _origin - _center;
        
        // TODO ....
        float angle = delta.getAngle();
        
        float dtAngle = dt * M_PI * 2;
        angle  = angle + dtAngle;
        
        Vec2 dest;
        dest.x = _center.x + r * sinf(angle);
        dest.y = _center.y + r * cosf(angle);
        
        _target->setPosition(dest);
    }
};

class MyAction2 : public ActionInterval
{
public:
    static MyAction2* create(float duration, Node* center, float r)
    {
        MyAction2* ret = new MyAction2;
        ret->init(duration, center, r);
        ret->autorelease();
        return ret;
    }
    
    // 被围绕的精灵
    Node* _centerNode;
    // 运动精灵的开始位置
    Vec2 _origin;
    // 开始运动时的半径
    float _r;
    // 开始运动时的圆心
    Vec2 _center;
    // 开始时运动的精灵和圆心的角度
    float _startAngle;
    
    bool init(float duration, Node* center, float r)
    {
        ActionInterval::initWithDuration(duration);
        _centerNode = center;
        _center = center->getPosition();
        _r = r;
        return true;
    }
    
    virtual void startWithTarget(Node *target)
    {
        ActionInterval::startWithTarget(target);
        _origin = target->getPosition();
      //  _r = _origin.getDistance(_center);
        
        _startAngle = (_origin - _center).getAngle();
    }
    
    // dt: 0 ~ 1表示运动的完成度
    void update(float dt)
    {
        float angle = dt * M_PI * 2;
        angle  = angle + _startAngle;
        
    //    CCLOG("angle = %g, dt = %g, r = %g", angle, dt, _r);
        
        Vec2 dest;
        dest.x = _centerNode->getPosition().x + _r * sinf(angle);
        dest.y = _centerNode->getPosition().y + _r * cosf(angle);
        
        
        
        _target->setPosition(dest);
    }
};



T07Action::T07Action()
{
}


T07Action::~T07Action()
{
}


bool T07Action::init()
{
    Layer::init();
    
#if 0
    // 动作演示，延时动作的By和To的区别
    {
        
        Sprite* sprite = Sprite::create("CloseNormal.png");
        MoveTo* move = MoveTo::create(2.0f, Vec2(100, 100));
        addChild(sprite);
        sprite->setPosition(400, 400);
        sprite->runAction(move);
    }
    
    {
        Sprite* sprite = Sprite::create("Images/blocks.png");
        MoveBy* move = MoveBy::create(2.0f, Vec2(100, 100));
        sprite->setPosition(400, 400);
        addChild(sprite);
        sprite->runAction(move);
    }
    
    ScaleTo;
    ScaleBy;
    
    JumpTo::create(3.0f, Vec2(100, 100), 30, 5);
    JumpBy::create(3.0f, Vec2(100, 100), 30, 5);
    
    RotateBy::create(3.0, 90);
    RotateTo::create(3.0, 90);
    
    BezierBy;
    BezierTo;
#endif
    
#if 0
    // 即时动作演示
    Place* place = Place::create(Vec2(100, 100));
    Sprite* sprite = Sprite::create("Iamges/blocks.png");
    addChild(sprite);
    sprite->runAction(place);
    // sprite->setPosition(100, 100);
    
    CallFunc* callfunc = CallFunc::create([](){
        
    });
    
    CallFuncN* callFuncN = CallFuncN::create([](Node*){
    
    });
    
    RemoveSelf* remove = RemoveSelf::create();
    sprite->runAction(remove); // sprite->removeFromParent();
#endif
    
#if 0
    // 自定义动作演示
    Sprite* center = Sprite::create("Images/blocks.png");
    addChild(center);
    center->setPosition(200, 200);
    
    Sprite* sprite = Sprite::create("CloseNormal.png");
    addChild(sprite);
    sprite->setPosition(100, 100);
    
    MyAction2* action = MyAction2::create(2, center, sprite->getPosition().getDistance(center->getPosition()));
    
     RepeatForever* rep = RepeatForever::create(action);
    sprite->runAction(rep);
    
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchMoved = [center](Touch* touch, Event*){
        center->setPosition(touch->getLocation());
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority
        (ev, this);
#endif
    
#if 0
    // 特效动作演示
    MoveBy* move = MoveBy::create(3.0f, Vec2(0, -200));
    EaseBounceOut* ease = EaseBounceOut::create(move);
    
    Sprite* sprite =Sprite::create("CloseNormal.png");
    addChild(sprite);
    sprite->setPosition(400, 400);
    
    sprite->runAction(ease);
#endif
    
    
#if 0
    // 动作干预
    // 1. runAction startAction
    // 2. stopAction stopAndRemove Action
    // 3. stopAllActions 消息使用
    
    Node::runAction(<#cocos2d::Action *action#>);
    Node::stopAction(cocos2d::Action *action);
    
    
    
    Node::stopAllActions();
    
    Node::stopActionByTag(100);
    
    
    MoveBy* move = MoveBy::create(2,Vec2(100, 100));
    move->setTag(100);
#endif
    
#if 0
    // TargetAction演示
    // Sequence
    Sprite* a = Sprite::create("CloseNormal.png");
    addChild(a);
    a->setPosition(Vec2(200, 200));
    
    Sprite* b = Sprite::create("CloseNormal.png");
    addChild(b);
    b->setPosition(Vec2(200, 300));
    
    MoveBy* move =MoveBy::create(1.0f, Vec2(100, 100));
    JumpBy* jump = JumpBy::create(1.0f, Vec2(100, 100), 30, 2);
    
    
    TargetedAction* target1 = TargetedAction::create(a, move);
  //  TargetedAction* target2 = TargetedAction::create(b, jump);
    
    Sequence* seq = Sequence::create(target1, jump, NULL);
    
    b->runAction(seq);
#endif
    
#if 0
    {
    MoveBy* move = MoveBy::create(5.0, Vec2(200, 200));
    Speed* s = Speed::create(move, 2);
    
    Sprite* a = Sprite::create("CloseNormal.png");
    addChild(a);
    a->setPosition(Vec2(200, 200));
    
    a->runAction(s);
    }
    {
        MoveBy* move = MoveBy::create(5.0, Vec2(200, 200));
      //  Speed* s = Speed::create(move, 2);
        
        Sprite* a = Sprite::create("CloseNormal.png");
        addChild(a);
        a->setPosition(Vec2(200, 300));
        
        a->runAction(move);
    }
#endif
    
    MoveBy* move = MoveBy::create(5.0, Vec2(200, 200));
    MoveBy* back = move->reverse();
    
    Sprite* a = Sprite::create("CloseNormal.png");
    addChild(a);
    a->setPosition(Vec2(200, 300));
    
    a->runAction(Sequence::create(move, back, NULL));
    
    
    
    
    return true;
}
