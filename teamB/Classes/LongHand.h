#ifndef _LONG_HAND_H_
#define _LONG_HAND_H_

#include "cocos2d.h"
USING_NS_CC;

class LongHand : public Sprite
{
public:
	CREATE_FUNC(LongHand);
	virtual bool init();

	//�j�̑傫��
	Size _handSize;
private:

};

#endif