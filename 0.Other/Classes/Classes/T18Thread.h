//
//  T18Thread.h
//  T0818
//
//  Created by 薛国良 on 15/11/4.
//
//

#ifndef __T0818__T18Thread__
#define __T0818__T18Thread__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class T18Thread : public Layer
{
public:
    CREATE_FUNC(T18Thread);
    bool init();
    
    Sprite* _sp1;
    Sprite* _sp2;
    int sock;
    
    Vec2 _pos;
    pthread_mutex_t _mutex;
    
    void update(float);
};

#endif /* defined(__T0818__T18Thread__) */
