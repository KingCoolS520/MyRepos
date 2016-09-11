#include "T01TextureCache.h"


T01TextureCache::T01TextureCache()
{
}


T01TextureCache::~T01TextureCache()
{
}


bool T01TextureCache::init()
{
	Layer::init();

	// 回调函数也是主线程调用
	const std::function<void(Texture2D*)> callback = [](Texture2D*)
	{
		CCLOG("load texture complete");
	};

	TextureCache* cache = Director::getInstance()->getTextureCache();

	CCLOG("load start");
	cache->addImageAsync("CloseNormal.png", callback);
	CCLOG("load end");

	return true;
}