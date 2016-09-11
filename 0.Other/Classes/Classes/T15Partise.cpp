//
//  T15Partise.cpp
//  T0818
//
//  Created by 薛国良 on 15/11/1.
//
//

#include "T15Partise.h"


bool T15Partise::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
#if 0
    // 内置的粒子效果
    auto particle = ParticleFire::create();
   // auto particle = ParticleGalaxy::create();
   // particle->setScale(5);
    addChild(particle);
    particle->setPosition(winSize.width/2, winSize.height/2);
    
    MoveBy* move= MoveBy::create(5.0f, Vec2(100, 0));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back, NULL);
    auto rep = RepeatForever::create(seq);
    
    particle->runAction(rep);
#endif
    
    // 自定义粒子
    auto particle = ParticleSystemQuad::create("Particles/Flower.plist");
    addChild(particle);
    particle->setPosition(winSize.width/2, winSize.height/2);
    
    return true;
}