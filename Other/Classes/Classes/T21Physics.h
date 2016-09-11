//
//  T21Physics.h
//  
//
//  Created by 薛国良 on 15/11/16.
//
//

#ifndef ____T21Physics__
#define ____T21Physics__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class T21Physics : public Layer
{
public:
    CREATE_FUNC(T21Physics);
    bool init();
    
    void onEnter();
    PhysicsWorld* _world;
    
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    
    DrawNode* _draw;
};
#endif /* defined(____T21Physics__) */
