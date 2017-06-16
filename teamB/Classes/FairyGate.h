#ifndef __FAIRY_GATE_H__
#define __FAIRY_GATE_H__

#include "cocos2d.h"
USING_NS_CC;

class FairyGate : public Sprite
{
public:
	CREATE_FUNC(FairyGate);

	bool init();
	float speed;

	void update(float delta);
	
private:

};
#endif