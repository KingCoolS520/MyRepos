//
//  T19Http.h
//  T0818
//
//  Created by 薛国良 on 15/11/5.
//
//

#ifndef __T0818__T19Http__
#define __T0818__T19Http__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "network/HttpClient.h"
using namespace network;

class T19Http:public Layer
{
public:
    CREATE_FUNC(T19Http);
    bool init();
    
    void response(HttpClient* client, HttpResponse* response);
};

#endif /* defined(__T0818__T19Http__) */
