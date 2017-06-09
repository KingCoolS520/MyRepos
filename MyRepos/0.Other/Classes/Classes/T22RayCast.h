//
//  T22RayCast.h
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#ifndef ____T22RayCast__
#define ____T22RayCast__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class T22RayCast : public Layer
{
public:
    CREATE_FUNC(T22RayCast);
    
    void onEnter();
    
    Sprite* _cat;
    int _r;
    int _angle;
    
    int _dist;
    PhysicsBody* _food;
    
    DrawNode* _draw;
    
    PhysicsWorld* _world;
    
    
    bool rayCastCallback(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    
    void update(float);
};

#endif /* defined(____T22RayCast__) */
