#ifndef _KNOB_H_
#define _KNOB_H_

#include "cocos2d.h"
USING_NS_CC;

class Knob : public Sprite
{
public:
	CREATE_FUNC(Knob);

	void startAnimation();
	void stopAnimation();

	virtual bool init();

private:
	Animation *animation;   //アニメーション
	Animate *action;
	RepeatForever *anime;

};

#endif