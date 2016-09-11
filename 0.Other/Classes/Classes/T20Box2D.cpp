//
//  T20Box2D.cpp
//  
//
//  Created by 薛国良 on 15/11/16.
//
//

#include "T20Box2D.h"

#define PTM 32.0f


#include "cocos2d.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

USING_NS_CC;

GLESDebugDraw::GLESDebugDraw()
: mRatio( 1.0f )
{
    this->initShader();
}

GLESDebugDraw::GLESDebugDraw( float32 ratio )
: mRatio( ratio )
{
    this->initShader();
}

void GLESDebugDraw::initShader( void )
{
    mShaderProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    
    mColorLocation = glGetUniformLocation( mShaderProgram->getProgram(), "u_color");
}

void GLESDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
    
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    b2Vec2* vertices = new b2Vec2[vertexCount];
    for( int i=0;i<vertexCount;i++)
    {
        vertices[i] = old_vertices[i];
        vertices[i] *= mRatio;
    }
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);
    
    
    CHECK_GL_ERROR_DEBUG();
    
    delete[] vertices;
#endif
    
}

void GLESDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
    
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    b2Vec2* vertices = new b2Vec2[vertexCount];
    for( int i=0;i<vertexCount;i++) {
        vertices[i] = old_vertices[i];
        vertices[i] *= mRatio;
    }
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);
    
    CHECK_GL_ERROR_DEBUG();
    
    delete[] vertices;
#endif
    
}

void GLESDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    const float32 k_segments = 16.0f;
    int vertexCount=16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    
    GLfloat*    glVertices = new (std::nothrow) GLfloat[vertexCount*2];
    for (int i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i*2]=v.x * mRatio;
        glVertices[i*2+1]=v.y * mRatio;
        theta += k_increment;
    }
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);
    
    CHECK_GL_ERROR_DEBUG();
    
    delete[] glVertices;
#endif
    
}

void GLESDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
    Vec2 centerOfCocos;
    centerOfCocos.x = center.x*PTM;
    centerOfCocos.y = center.y*PTM;
    DrawPrimitives::drawCircle(centerOfCocos, radius*PTM, 0, 100, false, 1, 1);
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    const float32 k_segments = 16.0f;
    int vertexCount=16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    
    GLfloat*    glVertices = new (std::nothrow) GLfloat[vertexCount*2];
    for (int i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i*2]=v.x * mRatio;
        glVertices[i*2+1]=v.y * mRatio;
        theta += k_increment;
    }
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
    // Draw the axis line
    DrawSegment(center,center+radius*axis,color);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);
    
    CHECK_GL_ERROR_DEBUG();
    
    delete[] glVertices;
#endif
    
}

void GLESDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    Vec2 pt1, pt2;
    pt1.x = p1.x * PTM;
    pt1.y = p1.y * PTM;
    
    pt2.x = p2.x * PTM;
    pt2.y = p2.y * PTM;
    
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
    DrawPrimitives::drawLine(pt1, pt2);
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
    GLfloat    glVertices[] =
    {
        p1.x * mRatio, p1.y * mRatio,
        p2.x * mRatio, p2.y * mRatio
    };
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    
    glDrawArrays(GL_LINES, 0, 2);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,2);
    
    CHECK_GL_ERROR_DEBUG();
#endif
    
}

void GLESDebugDraw::DrawTransform(const b2Transform& xf)
{

    b2Vec2 p1 = xf.p, p2;
    const float32 k_axisScale = 0.4f;
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1,0,0));
    
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    DrawSegment(p1,p2,b2Color(0,1,0));
}

void GLESDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
    //    glPointSize(size);
    
    GLfloat                glVertices[] = {
        p.x * mRatio, p.y * mRatio
    };
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    
    glDrawArrays(GL_POINTS, 0, 1);
    //    glPointSize(1.0f);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,1);
    
    CHECK_GL_ERROR_DEBUG();
#endif
    
}

void GLESDebugDraw::DrawString(int x, int y, const char *string, ...)
{
    //    NSLog(@"DrawString: unsupported: %s", string);
    //printf(string);
    /* Unsupported as yet. Could replace with bitmap font renderer at a later date */
}

void GLESDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1.0f);
#if 0
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
    GLfloat                glVertices[] = {
        aabb->lowerBound.x * mRatio, aabb->lowerBound.y * mRatio,
        aabb->upperBound.x * mRatio, aabb->lowerBound.y * mRatio,
        aabb->upperBound.x * mRatio, aabb->upperBound.y * mRatio,
        aabb->lowerBound.x * mRatio, aabb->upperBound.y * mRatio
    };
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
    
    CHECK_GL_ERROR_DEBUG();
#endif
    
}



bool T20Box2D::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
    // 创建世界，通过重力加速度参数
    b2Vec2 gravity = b2Vec2(0, -9.8);
    
    _world = new b2World( gravity );
   
    _draw.SetFlags(0xffff);
    _world->SetDebugDraw(&_draw);
    
    // 设置碰撞Listener
    _world->SetContactListener(this);
    
    {
        // 创建物体，物体要经过世界来创建
        // 参数是bodyDef，物体的定义
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(winSize.width/4/PTM, winSize.height/2/PTM);
    
        b2Body* body = _world->CreateBody(&def);
        _body3 = body;
    
        // body加外形
        b2CircleShape shape;
        shape.m_radius = 20/PTM; // ERROR
        b2Fixture* fixture = body->CreateFixture(&shape, 0.5);
        // 弹性系数
        fixture->SetRestitution(.7f);
        // 摩擦系统
        fixture->SetFriction(1);
        
        // 过滤碰撞
        b2Filter filter;
        filter.groupIndex = 0;
        filter.maskBits = 0x8 | 0x2;
        filter.categoryBits = 0x1;
       // fixture->SetFilterData(filter);
        
    
        // 到目前为止，我们看不见世界，也看不见body，因为b2Box只是处理物理数据
        Sprite* sprite = Sprite::create("CloseNormal.png");
      //  addChild(sprite);
    
        // 相互关联
        sprite->setUserData(body);
       // body->SetUserData(sprite);
        
        
        auto ev =EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [&, body](Touch* touch, Event*){
            
            
            Vec2 local1 = touch->getLocation();
            Vec2 center = Vec2(body->GetPosition().x*PTM, body->GetPosition().y*PTM);
            
            if(local1.getDistance(center) < body->GetFixtureList()->GetShape()->m_radius*PTM)
            {
                _pt1 = Vec2(body->GetPosition().x*PTM, body->GetPosition().y*PTM);
                return true;
            }
            return false;
        };
        
        ev->onTouchMoved = [&, body](Touch* touch, Event*){
            _pt2 = touch->getLocation();
        };
        
        
        
        ev->onTouchEnded = [&, body](Touch* touch, Event*){
            Vec2 local1 = touch->getStartLocation();
            Vec2 local2 = touch->getLocation();
            Vec2 dt = local2 - local1;
            
            b2Vec2 vec2 = b2Vec2(dt.x/10, dt.y/10);
            
            body->SetLinearVelocity(vec2);
            
            _pt1 = Vec2(0, 0);
            _pt2 = Vec2(0, 0);
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    }
#if 1
    
    // Body2
    {
        // 创建物体，物体要经过世界来创建
        // 参数是bodyDef，物体的定义
        b2BodyDef def;
      //  def.type = b2_dynamicBody;
        def.position.Set(winSize.width/2/PTM, winSize.height/2/PTM);
        
        b2Body* body = _world->CreateBody(&def);
        _body2 = body;
        
        // body加外形
        b2CircleShape shape;
        shape.m_radius = 20/PTM; // ERROR
        b2Fixture* fixture = body->CreateFixture(&shape, 0.5);
        // 弹性系数
        fixture->SetRestitution(.7f);
        
        // 到目前为止，我们看不见世界，也看不见body，因为b2Box只是处理物理数据
        Sprite* sprite = Sprite::create("CloseNormal.png");
        addChild(sprite);
        
        // 相互关联
        sprite->setUserData(body);
        body->SetUserData(sprite);
        
        
    }
    
    // Body3
    {
        // 创建物体，物体要经过世界来创建
        // 参数是bodyDef，物体的定义
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(winSize.width/3/PTM, winSize.height/4/PTM);
        
        b2Body* body = _world->CreateBody(&def);
        
        
        // body加外形
        b2CircleShape shape;
        shape.m_radius = 20/PTM; // ERROR
        b2Fixture* fixture = body->CreateFixture(&shape, 0.5);
        // 弹性系数
        fixture->SetRestitution(.7f);
        
        // 到目前为止，我们看不见世界，也看不见body，因为b2Box只是处理物理数据
        Sprite* sprite = Sprite::create("CloseNormal.png");
        addChild(sprite);
        
        // 相互关联
        sprite->setUserData(body);
        body->SetUserData(sprite);
        
        
    }
    // Body4
    {
        // 创建物体，物体要经过世界来创建
        // 参数是bodyDef，物体的定义
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(winSize.width/2/PTM, winSize.height/4/PTM);
        
        b2Body* body = _world->CreateBody(&def);
        
        // body加外形
        b2CircleShape shape;
        shape.m_radius = 20/PTM; // ERROR
        b2Fixture* fixture = body->CreateFixture(&shape, 0.5);
        // 弹性系数
        fixture->SetRestitution(.7f);
        
        // 到目前为止，我们看不见世界，也看不见body，因为b2Box只是处理物理数据
        Sprite* sprite = Sprite::create("CloseNormal.png");
        addChild(sprite);
        
        // 相互关联
        sprite->setUserData(body);
        body->SetUserData(sprite);
        
        
    }
    // Body5
    {
        // 创建物体，物体要经过世界来创建
        // 参数是bodyDef，物体的定义
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(winSize.width/5/PTM, winSize.height/4/PTM);
        
        b2Body* body = _world->CreateBody(&def);
        
        // body加外形
        b2CircleShape shape;
        shape.m_radius = 20/PTM; // ERROR
        b2Fixture* fixture = body->CreateFixture(&shape, 0.5);
        // 弹性系数
        fixture->SetRestitution(.7f);
        
        // 到目前为止，我们看不见世界，也看不见body，因为b2Box只是处理物理数据
        Sprite* sprite = Sprite::create("CloseNormal.png");
        addChild(sprite);
        
        // 相互关联
        sprite->setUserData(body);
        body->SetUserData(sprite);
        
        
    }
#endif
    scheduleUpdate();
    
    // 给世界加边界
    {
        b2BodyDef def;
        b2Body* body = _world->CreateBody(&def);
        
        b2EdgeShape shape;
        shape.Set(b2Vec2(0, 0), b2Vec2(winSize.width/PTM, 0));
        b2Fixture* fixture = body->CreateFixture(&shape, 0);
        
        // 过滤碰撞
        b2Filter filter;
        filter.groupIndex = 0;
        filter.categoryBits = 0x2;
        filter.maskBits = 0x5;
     //   fixture->SetFilterData(filter);
        
    }
    
    // 给世界加左边界
    {
        b2BodyDef def;
        b2Body* body = _world->CreateBody(&def);
        
        b2EdgeShape shape;
        shape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height/PTM));
        b2Fixture* fixture = body->CreateFixture(&shape, 0);
        
        // 过滤碰撞
        b2Filter filter;
        filter.groupIndex = 0;
        filter.categoryBits = 0x2;
        filter.maskBits = 0x5;
     //   fixture->SetFilterData(filter);
        
    }
    
    // 给世界加右边界
    {
        b2BodyDef def;
        b2Body* body = _world->CreateBody(&def);
        
        b2EdgeShape shape;
        shape.Set(b2Vec2(winSize.width/PTM, 0), b2Vec2(winSize.width/PTM, winSize.height/PTM));
        b2Fixture* fixture = body->CreateFixture(&shape, 0);
        
        // 过滤碰撞
        b2Filter filter;
        filter.groupIndex = 0;
        filter.categoryBits = 0x2;
        filter.maskBits = 0x5;
      //  fixture->SetFilterData(filter);
        
    }
    
#if 0
    b2DistanceJointDef def;
    def.bodyA = _body2;
    def.bodyB = _body3;
    
    b2Joint* j = _world->CreateJoint(&def);
#endif
    
    b2RopeJointDef def;
    def.bodyA = _body2;
    def.bodyB = _body3;
    def.localAnchorA = b2Vec2(0, 3);
    def.localAnchorB = b2Vec2(0, 0);
    def.maxLength = 2;
    _world->CreateJoint(&def);
    

    return true;
}

void T20Box2D::update(float dt)
{
    _world->Step(dt, 8, 1);
    
    // 遍历所有的body
    b2Body* body = _world->GetBodyList();
    while (body)
    {
        Sprite* sprite = (Sprite*)body->GetUserData();
        if(sprite)
        {
            b2Vec2 bodyPos = body->GetPosition();
            sprite->setPosition(bodyPos.x * PTM, bodyPos.y* PTM);
        }
        body = body->GetNext();
    }
}

