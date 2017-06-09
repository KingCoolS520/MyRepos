//
//  T17Socket.h
//  T0818
//
//  Created by 薛国良 on 15/11/2.
//
//

#ifndef __T0818__T17Socket__
#define __T0818__T17Socket__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class T17Socket : public Layer
{
public:
    CREATE_FUNC(T17Socket);
    bool init();
    
    Sprite* _sprite;
    int sock;
    
    Sprite* _sprite2;
    
    void update(float);
};

#endif /* defined(__T0818__T17Socket__) */
