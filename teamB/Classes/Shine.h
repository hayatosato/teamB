#ifndef __SHINE_H__
#define __SHINE_H__

#include "cocos2d.h"
#include <random>
USING_NS_CC;
using namespace std;

class Shine : public Sprite
{
public:
	CREATE_FUNC(Shine);

	bool init();

	void update(float delta);

private:
	void erase();

};
#endif