#include "T06RenderTexture.h"


T06RenderTexture::T06RenderTexture()
{
}


T06RenderTexture::~T06RenderTexture()
{
}


bool T06RenderTexture::init()
{
	Layer::init();

	auto size = Director::getInstance()->getWinSize();

	Sprite* sprite = Sprite::create("CloseNormal.png");
	addChild(sprite);

	sprite = Sprite::create("HelloWorld.png");
	addChild(sprite);

	sprite->setPosition(size.width / 2, size.height / 2);

	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [&](Touch*, Event*){

#if 0
		/* 拍照 */
		auto size = Director::getInstance()->getWinSize();
		RenderTexture* renderTexture = RenderTexture::create(size.width, size.height);

		Scene* scene = Director::getInstance()->getRunningScene();

		// 拍照
		renderTexture->beginWithClear(1, 1, 1, 1);
		this->visit(); // 绘制自己和所有儿子的内容
		renderTexture->end();

		/* 删除所有的精灵 */
		this->removeFromParent();

		// 到这里，旧场景的所有资源都已经删除掉了
		// 将照片贴到空场景上
		scene->addChild(renderTexture);

		renderTexture->setPosition(size.width / 2, size.height / 2);

		bool bRet = renderTexture->saveToFile("d:\\aaa.jpg");
		/* 释放旧场景资源 */
		Director::getInstance()->getTextureCache()->destroyInstance();
		SpriteFrameCache::getInstance()->destroyInstance();
		AnimationCache::getInstance()->destroyInstance();
#else
		utils::captureScreen([&](bool result, const std::string& filename){
			if (result)
			{
				Sprite* sprite = Sprite::create(filename);
				CCLOG("%s", filename.c_str());
				addChild(sprite);
			}
		}, "aaa.png");
#endif

//		Director::getInstance()->replaceScene(TransitionFade::create(2,  MyScene1::create()));
		return true;
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);

	return true;
}