#ifndef __KNOB_EFFECT_H__
#define __KNOB_EFFECT_H__

#include "cocos2d.h"
USING_NS_CC;

class KNobEffect : public Sprite 
{
public:
	CREATE_FUNC(KNobEffect);

	bool init();
	
private:
	void erase();
	ScaleTo* scaleBig;
	FadeOut* fade;
	CallFunc* callErase;
	Spawn* spa;
	Sequence* seq;


};
#endif