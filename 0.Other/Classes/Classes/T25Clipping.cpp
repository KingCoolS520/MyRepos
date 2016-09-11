//
//  T25Clipping.cpp
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#include "T25Clipping.h"


bool T25Clipping::init()
{
    Layer::init();
    
    auto winSize= Director::getInstance()->getWinSize();
    // 背景
    Label* label = Label::createWithSystemFont("www.itcast.cn", "Arial", 50);
    addChild(label);
    label->setPosition(winSize.width/2, winSize.height/2);
    
    
    ClippingNode* node = ClippingNode::create();
    addChild(node);
    
    
    // 遮挡
    LayerColor* layerColor = LayerColor::create(Color4B(0, 0, 0, 255));
    node->addChild(layerColor);
    
    // 模版
    Sprite* stencil = Sprite::create("elephant1_Diffuse.png");
    Rect rc = stencil->getTextureRect();
    rc.size.width /= 2;
    stencil->setTextureRect(rc);
    
   // LayerColor* stencil = LayerColor::create(Color4B::BLACK, 40, 30);
    Size size = stencil->getContentSize();
    CCLOG("size.width=%d, size.height=%d", (int)size.width, (int)size.height);
    
    
    stencil->setPosition(0, winSize.height/2);
    node->setStencil(stencil);
    
    MoveBy* move = MoveBy::create(2.0f, Vec2(winSize.width, 0));
    MoveBy* back = move->reverse();
    Sequence* seq = Sequence::create(move, back,NULL);
    RepeatForever* f = RepeatForever::create(seq);
    stencil->runAction(f);

    
#if 0
    Layer* layer = Layer::create();
    node->setStencil(layer);
    
    LayerColor* stencil = LayerColor::create(Color4B::BLACK, 40, 30);
    stencil->setOpacity(255);
    layer->addChild(stencil);
    stencil->setPosition(0, winSize.height/2-15);
#endif
    
    
    node->setInverted(true);
    node->setAlphaThreshold(0.05);
    
    
    return true;
}