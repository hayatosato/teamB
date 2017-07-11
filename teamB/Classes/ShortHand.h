#ifndef _SHORT_HAND_H_
#define _SHORT_HAND_H_

#include "cocos2d.h"
USING_NS_CC;

class ShortHand : public Sprite
{
public:
	CREATE_FUNC(ShortHand);
	virtual bool init();
	Sprite* bonusShine;
	void update(float delta);

private:
};

#endif