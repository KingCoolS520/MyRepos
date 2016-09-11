//
//  T26Clipping.cpp
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#include "T26Clipping.h"

bool T26Clipping::init()
{
    Layer::init();
    auto winSize = Director::getInstance()->getWinSize();
    
    Sprite* sprite = Sprite::create("bg1.png");
    addChild(sprite);
    sprite->setPosition(winSize/2);
    
    Sprite* button = Sprite::create("CloseNormal.png");
    addChild(button);
    button->setPosition(100, 100);
    
    ClippingNode* node = ClippingNode::create();
    addChild(node);
    
    // 半透明的遮盖
    LayerColor* layerColor = LayerColor::create(Color4B(166, 166, 166, 166));
    node->addChild(layerColor);
    
    // 焦点
    Layer* stencil = Layer::create();
    node->setStencil(stencil);
    
    
        Sprite* button1 = Sprite::create("CloseNormal.png");
        button1->setPosition(100, 100);
        stencil->addChild(button1);
    
    
    node->setInverted(true);
    node->setAlphaThreshold(0.05f);
    
    _hand = Sprite::create("Images/b1.png");
    layerColor->addChild(_hand);
    _hand->setPosition(button1->getPosition() + Vec2(button1->getBoundingBox().size.width/2 + _hand->getBoundingBox().size.width/2+3, 0));
    
    return true;
}