#include "T05BatchNode.h"


T05BatchNode::T05BatchNode()
{
}


T05BatchNode::~T05BatchNode()
{
}


bool T05BatchNode::init()
{
	Layer::init();

	auto size = Director::getInstance()->getWinSize();

	Sprite* sprite = Sprite::create("CloseNormal.png");
	addChild(sprite);

	sprite = Sprite::create("HelloWorld.png");
	addChild(sprite);

#if 0
	SpriteBatchNode* node = SpriteBatchNode::create("CloseNormal.png");
	addChild(node);

	for (int i = 0; i < 10000; ++i)
	{
		Sprite* sprite = Sprite::createWithTexture(node->getTexture());
		node->addChild(sprite);
		sprite->setPosition(size.width*CCRANDOM_0_1(), size.height*CCRANDOM_0_1());
	}
#endif

	return true;
}