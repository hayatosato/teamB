#ifndef __JUNK_H__
#define __JUNK_H__

#include "cocos2d.h"
#include <random>
USING_NS_CC;
using namespace std;

class Junk : public Sprite
{
public:
	static Junk *create(int junkNum);

	bool init(int junkNum);

	void update(float delta);
private:
	float downSpeed;          //d—Í
	float directionSpeed;     //¶‰E‚Ö‚Ì—Í

	void up();
	void fadeErase(float delta);
	void erase();

};
#endif