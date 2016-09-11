//
//  T27Shader.h
//  
//
//  Created by 薛国良 on 15/11/17.
//
//

#ifndef ____T27Shader__
#define ____T27Shader__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class T27Shader: public Layer
{
public:
    CREATE_FUNC(T27Shader);
    
    GLProgramState* _glProgramState;
    GLProgramState* _oldProgram;
    
    void onExit()
    {
        Layer::onExit();
        _oldProgram->release();
    }
    
    bool init()
    {
        Layer::init();
        
        auto winSize = Director::getInstance()->getWinSize();
        Sprite* sprite = Sprite::create("elephant1_Diffuse.png");
        addChild(sprite);
        sprite->setPosition(winSize/2);
        
        _oldProgram = sprite->getGLProgramState();
        _oldProgram->retain();
        
        // 创建GLProgram
        std::string str;
        str = FileUtils::getInstance()->getStringFromFile("Shaders/example_outline.fsh");
        GLProgram* program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, str.c_str());
        
        _glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
       // _glProgramState = GLProgramState::create(program);
        
        // 设置到生效的节点中
        // sprite->setGLProgram(program);
        
        Vec3 color(1.0f, 0.2f, 0.3f);
        GLfloat radius = 0.01f;
        GLfloat threshold = 1.75;
        
        _glProgramState->setUniformVec3("u_outlineColor", color);
        _glProgramState->setUniformFloat("u_radius", radius);
        _glProgramState->setUniformFloat("u_threshold", threshold);
        
        
        auto ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [=](Touch* touch, Event*)
        {
            Vec2 pos = touch->getLocation();
            if(sprite->getBoundingBox().containsPoint(pos))
            {
                sprite->setGLProgramState(_glProgramState);
                return true;
            }
           
            return false;
        };
        ev->onTouchEnded = [=](Touch* touch, Event*){
            sprite->setGLProgramState(_oldProgram);
        };
        ev->onTouchMoved = [=](Touch* touch, Event*){
            Vec2 pos = touch->getLocation();
            if(sprite->getBoundingBox().containsPoint(pos))
            {
                sprite->setGLProgramState(_glProgramState);
            }
            else
            {
                sprite->setGLProgramState(_oldProgram);
            }
        };
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
        
        return true;
    }
};

#endif /* defined(____T27Shader__) */
