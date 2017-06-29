#ifndef __EFFECT_FAIRY_H__
#define __EFFECT_FAIRY_H__

#include "cocos2d.h"
USING_NS_CC;

class EffectFairy : public Sprite
{
public:
	CREATE_FUNC(EffectFairy);

	bool init();

	
private:
	Animation *animation;
	Animate *action;
	RepeatForever *anime;


};
#endif