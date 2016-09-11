//
//  T24ClippingNode.cpp
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#include "T24ClippingNode.h"


bool T24ClippingNode::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
#if 0
    
    // ClippingNode 基础
    // 外面的世界  背景
    LayerColor* layer1 = LayerColor::create(Color4B::RED);
    addChild(layer1);
    
    Sprite* bg = Sprite::create("bg1.png");
    addChild(bg);
    bg->setPosition(winSize.width/2, winSize.height/2);
    
    // 阻挡的东西
    LayerColor* layer2 = LayerColor::create(Color4B::GREEN);
  //  addChild(layer2);
    
    ClippingNode* node = ClippingNode::create();
    addChild(node);
    node->addChild(layer2);
    
    // 扣开的窗口
   // LayerColor* layer3 = LayerColor::create(Color4B(255, 255, 255, 0));
    
    Layer* layer = Layer::create();
    Sprite* sprite = Sprite::create("elephant1_Diffuse.png");
    // 通过setStencil加入的内容，其实是裁剪
    node->setStencil(layer);
    
    layer->addChild(sprite);
    sprite->setPosition(winSize.width/2, winSize.height/2);
    
    
    Sprite* closeNormal = Sprite::create("CloseNormal.png");
    layer->addChild(closeNormal);
    
    closeNormal->setPosition(100, 100);
    
    //
    node->setInverted(true);
    node->setAlphaThreshold(0.05);
    
    // 移动大象
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchMoved = [=](Touch* touch, Event*){
        sprite->setPosition(touch->getLocation());
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif
    
    // 鳄鱼洗澡
    Sprite* bg = Sprite::create("bg1.png");
    addChild(bg);
    bg->setPosition(winSize.width/2, winSize.height/2);
    
    ClippingNode* node = ClippingNode::create();
    addChild(node);
    
    // 覆盖层
    LayerColor* layer2 = LayerColor::create(Color4B(0, 255, 0, 166));
    node->addChild(layer2);
    
    // 模版层
    Layer* stencil = StencilLayer::create();
    node->setStencil(stencil);
    
    //
    node->setInverted(true);
    node->setAlphaThreshold(0.05);
    
    return true;
}