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

// 先构造 -> onEnter -> xxxxxx -> onExit -> 析构

// 场景A 场景B
// A -> B
// A->onEnter A->onExit B->onEnter B->onExit

void T03Node::onEnter()
{
	/* 调用父类的onEnter */
	Layer::onEnter();

	// 如果忘记调用父类的onEnter，那么场景的定时器无效，触摸无效，动作也无效

	CCLOG("T03Node::onEnter");
	
}

void T03Node::onExit()
{
	CCLOG("T03Node::onExit");

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	/* 调用父类的onExit */
	Layer::onExit();
}