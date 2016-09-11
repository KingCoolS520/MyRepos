//
//  T20Box2D.h
//  
//
//  Created by 薛国良 on 15/11/16.
//
//

#ifndef ____T20Box2D__
#define ____T20Box2D__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

#include "../external/Box2D/Box2D.h"

struct b2AABB;

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class GLESDebugDraw : public b2Draw
{
    float32 mRatio;
    cocos2d::GLProgram* mShaderProgram;
    GLint        mColorLocation;
    
    void initShader( void );
public:
    GLESDebugDraw();
    
    GLESDebugDraw( float32 ratio );
    
    virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
    
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
    
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    
    virtual void DrawTransform(const b2Transform& xf);
    
    virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
    
    virtual void DrawString(int x, int y, const char* string, ...);
    
    virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
};



class T20Box2D : public Layer, b2ContactListener
{
public:
    CREATE_FUNC(T20Box2D);
    bool init();
    
    
    Vec2 _pt1;
    Vec2 _pt2;
    void drawCallback()
    {
        // 实现自定义的绘制
        _world->DrawDebugData();
                
        DrawPrimitives::drawLine(_pt1, _pt2);
        
        //DrawPrimitives::drawLine(Vec2(0, 0), Vec2(100, 100));
    }
    
    CustomCommand _customCommand;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        _customCommand.init(getGlobalZOrder(), transform, 0);
        _customCommand.func = CC_CALLBACK_0(T20Box2D::drawCallback, this);
        renderer->addCommand(&_customCommand);
    }
   
    
    // 世界
    b2World* _world;
    b2Body* _body2;
    b2Body* _body3;
    void update(float);
    
    virtual void BeginContact(b2Contact* contact)
    {
        contact->GetFixtureA()->GetBody()->GetUserData();
        contact->GetFixtureB()->GetBody()->GetUserData();
        
        CCLOG("BEGIN");
    }
    
    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact) {
        CCLOG("END");
    }
    
#if 0
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
        CCLOG("PreSolve");
    }
    
    
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        CCLOG("PostSolve");
    }
#endif
    
    
    GLESDebugDraw _draw;
};

#endif /* defined(____T20Box2D__) */
