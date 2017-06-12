#ifndef __DEATH_FAIRY_H__
#define __DEATH_FAIRY_H__

#include "cocos2d.h"
USING_NS_CC;

class DeathFairy : public Sprite
{
public:
	CREATE_FUNC(DeathFairy);

	float normalScale;

	ScaleTo*  scale;
	Sequence* seq;
	CallFunc* call;

	bool init();
	
private:
	void erase();
};
#endif