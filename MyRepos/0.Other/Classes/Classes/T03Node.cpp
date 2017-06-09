#include "T03Node.h"


T03Node::T03Node()
{
	CCLOG("T03Node::T03Node");
	
}


T03Node::~T03Node()
{
	CCLOG("T03Node::~T03Node");
	
}


bool T03Node::init()
{
	Layer::init();

	MyDrawNode* myNode = MyDrawNode::create();
	addChild(myNode, 1);


	Sprite* sprite = Sprite::create("blocks.png");
	addChild(sprite);

	sprite->setPosition(200, 200);

	auto ev = EventListenerTouchOneByOne::create();

	ev->onTouchBegan = [](Touch*, Event*){
		TransitionFade* scene = TransitionFade::create(2, MyScene::create());
		Director::getInstance()->replaceScene(MyScene::create());
		return true; };
	ev->onTouchMoved = [=](Touch* touch, Event*)
	{
		// sprite->setPosition(touch->getLocation());
		
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);

//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile();
	
//	Sprite* sprite = Sprite::create("aaa.jpg");
//	sprite->setOpacity(0);


	return true;
}

// �ȹ��� -> onEnter -> xxxxxx -> onExit -> ����

// ����A ����B
// A -> B
// A->onEnter A->onExit B->onEnter B->onExit

void T03Node::onEnter()
{
	/* ���ø����onEnter */
	Layer::onEnter();

	// ������ǵ��ø����onEnter����ô�����Ķ�ʱ����Ч��������Ч������Ҳ��Ч

	CCLOG("T03Node::onEnter");
	
}

void T03Node::onExit()
{
	CCLOG("T03Node::onExit");

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	/* ���ø����onExit */
	Layer::onExit();
}