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
		/* ���� */
		auto size = Director::getInstance()->getWinSize();
		RenderTexture* renderTexture = RenderTexture::create(size.width, size.height);

		Scene* scene = Director::getInstance()->getRunningScene();

		// ����
		renderTexture->beginWithClear(1, 1, 1, 1);
		this->visit(); // �����Լ������ж��ӵ�����
		renderTexture->end();

		/* ɾ�����еľ��� */
		this->removeFromParent();

		// ������ɳ�����������Դ���Ѿ�ɾ������
		// ����Ƭ�����ճ�����
		scene->addChild(renderTexture);

		renderTexture->setPosition(size.width / 2, size.height / 2);

		bool bRet = renderTexture->saveToFile("d:\\aaa.jpg");
		/* �ͷžɳ�����Դ */
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