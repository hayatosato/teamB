#ifndef __CLEAR_H__
#define __CLEAR_H__

#include "cocos2d.h"
#include "EffectFairy.h"
USING_NS_CC;

class Clear : public Node
{
public:
	CREATE_FUNC(Clear);

	bool init();
	
private:
	Sprite* clear;
	EffectFairy* fairyOne;
	EffectFairy* fairyTwo;
};
#endif