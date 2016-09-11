#ifndef __T02SpriteFrame_H__
#define __T02SpriteFrame_H__

#include "cocos2d.h"
USING_NS_CC;

class T02SpriteFrame : public Layer
{
public:
	T02SpriteFrame();
	~T02SpriteFrame();

	CREATE_FUNC(T02SpriteFrame);

	bool init();

	int _count;
	int _loadedCount;
	ProgressTimer* _progress;

	void loadImageCallback(Texture2D*);
#if 0
	void update(float dt);
#endif

};

#endif

