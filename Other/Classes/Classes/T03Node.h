#ifndef __T03Node_H__
#define __T03Node_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

/*
	���ֵĲ��ź�ֹͣ��
	1.��onEnterTransitionDidFinish����
	2.��onExitֹͣ�����

	ȫ�ֵı����ĳ�ʼ�����ͷ�
	1. ����

*/

class MyDrawNode : public Node
{
public:
	CREATE_FUNC(MyDrawNode);

	CustomCommand _cmd;
	void onDraw()
	{
		DrawPrimitives::drawCircle(Vec2(200, 200), 80, 0, 30, true);
	}

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
	{
		// ��ô����...
		// ���ͻ��������OpenGL
		_cmd.init(this->getGlobalZOrder());
		_cmd.func = std::bind(&MyDrawNode::onDraw, this);
		
		// ��cocos�ײ㷢�ͻ�������
		renderer->addCommand(&_cmd);
	}
};

class MyScene : public Scene
{
public:
	CREATE_FUNC(MyScene);

	MyScene()
	{
		CCLOG("MyScene::MyScene");
		
	}

	~MyScene()
	{
		CCLOG("MyScene::~MyScene");
		
	}

	void onEnterTransitionDidFinish()
	{
		

		SimpleAudioEngine::getInstance()->playBackgroundMusic("2.mp3", true);
		Scene::onEnterTransitionDidFinish();
		CCLOG("MyScene::onEnterTransitionDidFinish");
	}
	void onExitTransitionDidStart()
	{
		Scene::onExitTransitionDidStart();
		CCLOG("MyScene::onExitTransitionDidStart");
	}

	void onEnter()
	{
		CCLOG("MyScene::onEnter");
		
		Scene::onEnter();
	}
	void onExit()
	{
		CCLOG("MyScene::onExit");
		Scene::onExit();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
};

class T03Node : public Layer
{
public:
	T03Node();
	~T03Node();

	CREATE_FUNC(T03Node);

	bool init();

	void onEnterTransitionDidFinish()
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("1.mp3", true);
		Layer::onEnterTransitionDidFinish();
		CCLOG("T03Node::onEnterTransitionDidFinish");
	}
	void onExitTransitionDidStart()
	{
		Layer::onExitTransitionDidStart();
		CCLOG("T03Node::onExitTransitionDidStart");
	}
	void onEnter();
	void onExit();
#if 0
	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
	{
	}
#endif
};

#endif
