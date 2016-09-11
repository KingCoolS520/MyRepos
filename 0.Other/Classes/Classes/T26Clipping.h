//
//  T26Clipping.h
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#ifndef ____T26Clipping__
#define ____T26Clipping__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class T26Clipping: public Layer
{
public:
    CREATE_FUNC(T26Clipping);
    bool init();
    
    Sprite* _hand;
};

#endif /* defined(____T26Clipping__) */
