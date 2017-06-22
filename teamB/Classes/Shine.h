#ifndef __SHINE_H__
#define __SHINE_H__

#include "cocos2d.h"
#include <random>
USING_NS_CC;
using namespace std;

class Shine : public Sprite
{
public:
	static Shine *create(bool mode);

	bool init(bool mode);
	bool numberMode;

	void update(float delta);

private:
	void erase();

};
#endif