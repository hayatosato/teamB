#ifndef _LONG_HAND_H_
#define _LONG_HAND_H_

#include "cocos2d.h"
USING_NS_CC;

class LongHand : public Sprite
{
public:
	CREATE_FUNC(LongHand);

	Sprite* road;

	virtual bool init();
private:

	void update(float delta);

};

#endif