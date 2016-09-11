//
//  T24ClippingNode.h
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#ifndef ____T24ClippingNode__
#define ____T24ClippingNode__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class StencilLayer: public Layer
{
public:
    CREATE_FUNC(StencilLayer);
    
#if 0
    std::vector<Vec2> _pts;
    
    
    CustomCommand _command;
    void drawCallback()
    {
        if(_pts.size() == 0)
            return;
        
      //  glLineWidth(5);
    
        
        std::vector<Vec2>::iterator it = _pts.begin();
       // Vec2 pt1 = *it;
        for (it=_pts.begin(); it!=_pts.end(); ++it) {
            Vec2 pt2 = *it;
         //   DrawPrimitives::drawLine(pt1, pt2);
            
            
          //  pt1 = pt2;
        }
    }
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        _command.init(getGlobalZOrder(), transform, 0);
        _command.func = CC_CALLBACK_0(StencilLayer::drawCallback, this);
        renderer->addCommand(&_command);
    }
#endif
    
    
    
    bool init()
    {
        Layer::init();
        
        auto ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [](Touch*, Event*){return true;};
        ev->onTouchMoved = [&](Touch* touch, Event*){
          //  _pts.push_back(touch->getLocation());
            Sprite* sprite = Sprite::create("CloseNormal.png");
            sprite->setScale(0.5f);
            addChild(sprite);
            sprite->setPosition(touch->getLocation());
        };
        ev->onTouchEnded = [](Touch*, Event*){};
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
        
        return true;
    }
};

class T24ClippingNode : public Layer
{
public:
    CREATE_FUNC(T24ClippingNode);
    bool init();
};

#endif /* defined(____T24ClippingNode__) */
