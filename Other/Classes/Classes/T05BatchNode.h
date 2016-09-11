#ifndef __T05BatchNode_H__
#define __T05BatchNode_H__

#include "cocos2d.h"
USING_NS_CC;

class T05BatchNode : public Layer
{
public:
	T05BatchNode();
	~T05BatchNode();

	CREATE_FUNC(T05BatchNode);

	bool init();
};

#endif

