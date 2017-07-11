#ifndef __SURGE_NUM_H__
#define __SURGE_NUM_H__

#include "cocos2d.h"
USING_NS_CC;

class SurgeNum : public Sprite
{
public:
	static SurgeNum *create(int num, int way);

	bool init(int num, int way);
	void erase();

	void update(float delta);
private:

};
#endif