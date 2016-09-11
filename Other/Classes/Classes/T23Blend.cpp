//
//  T23Blend.cpp
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#include "T23Blend.h"

bool T23Blend::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
#if 0
    
    
    LayerColor* layer1 = LayerColor::create(Color4B(255, 0, 0, 255));
    addChild(layer1);
    
    LayerColor* layer2 = LayerColor::create(Color4B(0, 255, 0, 128), winSize.width/2, winSize.height/2);
    addChild(layer2);
    
 //   GL_ONE, GL_ONE_MINUS_SRC_ALPHA;
    
    BlendFunc blend;
    blend.src = GL_ONE;   // 即将要渲染的颜色
    blend.dst = GL_ONE_MINUS_SRC_ALPHA;    // 背景原有颜色
    layer2->setBlendFunc(blend);
    // 混合：奖源和目标的颜色混合（相加）在一起做为该位置的新颜色
#endif
    
    Sprite* sprite1 = Sprite::create("bg1.png");
    addChild(sprite1);
    sprite1->setPosition(winSize.width/2, winSize.height/2);
    
    Sprite* sprite2 = Sprite::create("bg2.png");
    addChild(sprite2);
    sprite2->setPosition(winSize.width/2, winSize.height/2);
    
  //  sprite2->setOpacity(128);
    BlendFunc func;
    func.src = GL_ONE_MINUS_SRC_ALPHA;                 // 即将要渲染的颜色
    func.dst = GL_ONE; // 背景原有颜色
    sprite2->setBlendFunc(func);
    
    FadeOut* fadeOut = FadeOut::create(3.0f);
    FadeIn* fadeIn = FadeIn::create(3.0f);
    Sequence* seq = Sequence::create(fadeOut, fadeIn, NULL);
    RepeatForever* rep = RepeatForever::create(seq);
    sprite2->runAction(rep);
    
    return true;
}
