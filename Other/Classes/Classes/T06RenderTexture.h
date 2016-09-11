#ifndef __T06RenderTexture_H__
#define __T06RenderTexture_H__

#include "cocos2d.h"
USING_NS_CC;

class MyScene1 : public Scene
{
public:
	CREATE_FUNC(MyScene1);

	bool init()
	{
		Scene::init();

		Sprite* sprite = Sprite::create("Images/assetMgrBackground2.png");
		addChild(sprite);
		sprite->setPosition(200, 200);

		return true;
	}


};

class T06RenderTexture : public Layer
{
public:
	T06RenderTexture();
	~T06RenderTexture();

	CREATE_FUNC(T06RenderTexture);

	bool init();
};

#endif

