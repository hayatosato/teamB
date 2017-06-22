#ifndef __DEATH_FAIRY_H__
#define __DEATH_FAIRY_H__

#include "cocos2d.h"
USING_NS_CC;

class DeathFairy : public Sprite
{
public:
	static DeathFairy *create(int actionMode);

	float normalScale;

	ScaleTo*  scale;
	FadeOut*  fadeOut;
	Sequence* seq;
	CallFunc* call;

	bool init(int actionMode);
	
private:
	void erase();
};
#endif