#ifndef __T01TextureCache_H__
#define __T01TextureCache_H__

#include "cocos2d.h"
USING_NS_CC;

class T01TextureCache : public Layer
{
public:
	T01TextureCache();
	~T01TextureCache();

	CREATE_FUNC(T01TextureCache);

	bool init();
};

#endif

