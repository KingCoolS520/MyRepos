#include "T02SpriteFrame.h"


T02SpriteFrame::T02SpriteFrame()
{
}


T02SpriteFrame::~T02SpriteFrame()
{
}

const char* files[] = {
	"ActionTimeline/Default/Button_Disable.png",
	"ActionTimeline/Default/Sprite.png",
	"ActionTimeline/testAnimationResource/1.png",
	"ActionTimeline/testAnimationResource/2.png",
	"ActionTimeline/testAnimationResource/3.png",
	"ActionTimeline/testAnimationResource/4.png",
	"ActionTimeline/testAnimationResource/5.png",
	"ActionTimeline/testAnimationResource/6.png",
	"ActionTimeline/testAnimationResource/7.png",
	"ActionTimeline/testAnimationResource/8.png",
	"ActionTimeline/testAnimationResource/hat.png",
	"animations/dragon_animation.png",
	"animations/ghosts.png",
	"animations/grossini-aliases.png",
	"animations/grossini.png",
	"animations/grossini_blue.png",
	"animations/grossini_family.png",
	"animations/grossini_gray.png",
	"bg1.png",
	"bg2.png",
	"blocks.png",
	"ccb/animated-grossini.png",
	"ccb/btn-a-0.png",
	"ccb/btn-a-1.png",
	"ccb/btn-a-2.png",
	"ccb/btn-b-0.png",
	"ccb/btn-b-1.png",
	"ccb/btn-b-2.png",
	"ccb/btn-back-0.png",
	"ccb/btn-back-1.png",
	"ccb/btn-test-0.png",
	"ccb/btn-test-1.png",
	"ccb/btn-test-2.png",
	"ccb/burst.png",
	"ccb/ccbParticleStars.png",
	"ccb/grossini-generic.png",
	"ccb/jungle-left.png",
	"ccb/jungle-right.png",
	"ccb/jungle.png",
	"ccb/logo-icon.png",
	"ccb/logo.png",
	"ccb/markerfelt24shadow.png",
	"ccb/particle-fire.png",
	"ccb/particle-smoke.png",
	"ccb/particle-snow.png",
	"ccb/particle-stars.png",
	"ccb/scale-9-demo.png",
	"ccs-res/armature/bear0.png",
	"ccs-res/armature/Cowboy0.png",
	"ccs-res/armature/cyborg.png",
	"ccs-res/armature/Default/DemoPlayer0.png",
	"ccs-res/armature/Dragon.png",
	"ccs-res/armature/hero0.png",
	"ccs-res/armature/HeroAnimation0.png",
	"ccs-res/armature/horse0.png",
	"ccs-res/armature/knight.png",
	"ccs-res/armature/robot.png",
	"ccs-res/armature/testEasing0.png",
	"ccs-res/armature/weapon.png",
	"ccs-res/CocosStudio3DTest/textures/pump_flare_04.png",
	"ccs-res/CocosStudio3DTest/textures/pump_streak_03.png",
	"ccs-res/cocosui/100/1000.png",
	"ccs-res/cocosui/animationbuttonnormal.png",
	"ccs-res/cocosui/animationbuttonpressed.png",
	"ccs-res/cocosui/arrow.png",
	"ccs-res/cocosui/b11.png",
	"ccs-res/cocosui/backtotopnormal.png",
	"ccs-res/cocosui/backtotoppressed.png",
	"ccs-res/cocosui/bitmapFontTest2.png",
	"ccs-res/cocosui/button.png",
	"ccs-res/cocosui/buttonHighlighted.png",
	"ccs-res/cocosui/ccicon.png",
	"ccs-res/cocosui/check_box_active.png",
	"ccs-res/cocosui/check_box_active_disable.png",
	"ccs-res/cocosui/check_box_active_press.png",
	"ccs-res/cocosui/check_box_normal.png",
	"ccs-res/cocosui/check_box_normal_disable.png",
	"ccs-res/cocosui/check_box_normal_press.png",
	"ccs-res/cocosui/CloseNormal.png",

};

#if 0
void T02SpriteFrame::update(float)
{
	if (_loadedCount == _count) return;

	Director::getInstance()->getTextureCache()->addImage(files[_loadedCount++]);
	_progress->setPercentage(_loadedCount * 100 / _count);
}
#endif

void T02SpriteFrame::loadImageCallback(Texture2D*)
{
	this->_loadedCount++;

	_progress->setPercentage(_loadedCount * 100 / _count);

	if (this->_loadedCount == this->_count)
	{
		CCLOG("load end");
	}
}


bool T02SpriteFrame::init()
{
	Layer::init();

	auto size = Director::getInstance()->getWinSize();

	// 来一个进度条控件
	Sprite* sprite = Sprite::create("loadingbar.png");

	ProgressTimer* progress = ProgressTimer::create(sprite);
	_progress = progress;
	addChild(progress);
	progress->setPosition(size.width / 2, size.height / 2);

	// 改成条状
	progress->setType(ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0, 0));
	progress->setBarChangeRate(Vec2(1, 0));

	//progress->setPercentage(50);
	_loadedCount = 0;
	_count = sizeof(files) / sizeof(*files);

//	scheduleUpdate();

	for (int i = 0; i < _count; ++i)
	{
	//	Director::getInstance()->getTextureCache()->
	//		addImageAsync(files[i], std::bind(&T02SpriteFrame::loadImageCallback, this, std::placeholders::_1));
		//	Director::getInstance()->getTextureCache()->
		//		addImageAsync(files[i], CC_CALLBACK_1(T02SpriteFrame::loadImageCallback, this));
			Director::getInstance()->getTextureCache()->
				addImageAsync(files[i], [&](Texture2D*){
					this->_loadedCount++;

					_progress->setPercentage(_loadedCount * 100 / _count);

					if (this->_loadedCount == this->_count)
					{
						CCLOG("load end");
					}
			});
	}

#if 0
	// 矩形所使用的坐标体系是以左上角为原点的坐标体系
	SpriteFrame* frame = SpriteFrame::create("HelloWorld.png",", Rect(10, 10, 50, 50));
	SpriteFrame* frame2 = SpriteFrame::create("HelloWorld.png",", Rect(100, 100, 50, 50));

	SpriteFrameCache::getInstance()->addSpriteFrame(frame, "FrameName");
	
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("FrameName");

	// 销毁所有的精灵帧
	SpriteFrameCache::getInstance()->destroyInstance();
	// 销毁某个精灵帧
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("FrameName");

	Sprite* sprite = Sprite::createWithSpriteFrame(frame);
	sprite = Sprite::createWithSpriteFrameName("FrameName");

	{
		// 使用整个图片作为精灵帧使用
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png",");
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("aaa.plist");
#endif
	return true;
}