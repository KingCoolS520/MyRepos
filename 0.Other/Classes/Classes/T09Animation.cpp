//
//  T09Animation.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#include "T09Animation.h"


bool T09Animation::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
    {
    // 演示1:使用小图片来创建动画
        Vector<SpriteFrame*> frames;
        for(int i=0;i <4; ++i)
        {
            char path[256];
            sprintf(path, "Plane/shoot/enemy1_down%d.png", i+1);
            
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
            
            Size size = texture->getContentSize();
            SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));
            
            frames.pushBack(frame);
        }
        
        Animation* animation = Animation::createWithSpriteFrames(frames);
        animation->setDelayPerUnit(0.1f);
        
        AnimationCache::getInstance()->addAnimation(animation, "MyAnimation");
        
        Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("MyAnimation"));
        
        Sprite* sprite = Sprite::create();
        sprite->setPosition(winSize.width/2, winSize.height/2);
        addChild(sprite);
        sprite->runAction(RepeatForever::create(animate));
        
        //
        Animate* animate2 = Animate::create(animation);
        Sprite* sprite2 = Sprite::create();
        sprite2->runAction(RepeatForever::create(animate2));
        addChild(sprite2);
        sprite2->setPosition(200, 200);
    }
    
    // 演示2:通过大图来创建动画
    {
        // 解析plist文件，并且把大图中的小图作为精灵帧加入到缓存
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/grossini_blue.plist");
        
        // 把精灵帧从缓存中获取，并加入到数组
        Vector<SpriteFrame*> frames;
        for(int i=0; i<4; ++i)
        {
            char name[256];
            sprintf(name, "grossini_blue_%02d.png", i+1);
            
            SpriteFrameCache* cache = SpriteFrameCache::getInstance();
            SpriteFrame* frame = cache->getSpriteFrameByName(name);
            frames.pushBack(frame);
        }
        
        Animation* animation = Animation::createWithSpriteFrames(frames);
        animation->setDelayPerUnit(0.1f);
        
        Animate* animate2 = Animate::create(animation);
        Sprite* sprite2 = Sprite::create();
        sprite2->runAction(RepeatForever::create(animate2));
        addChild(sprite2);
        sprite2->setPosition(200, 200);
    }
#if 0
    {
        AnimationCache* cache = AnimationCache::getInstance();
        cache->addAnimation(animation, "MyAnimation");
        cache->removeAnimation("MyAnimation");
        cache->destroyInstance(); // 全删除，往往用在场景切换
        cache->getAnimation("MyAnimation");
    }
#endif
    
    
    return true;
}