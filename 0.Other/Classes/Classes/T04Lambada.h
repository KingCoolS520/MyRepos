#ifndef __T04Lambada_H__
#define __T04Lambada_H__

#include "cocos2d.h"
USING_NS_CC;

class T04Lambada : public Layer
{
public:
	T04Lambada();
	~T04Lambada();

	CREATE_FUNC(T04Lambada);

	Sprite* _sprite;

	bool init();
};

#endif

