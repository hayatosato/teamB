#ifndef __JUNK_H__
#define __JUNK_H__

#include "cocos2d.h"
#include <random>
USING_NS_CC;
using namespace std;

class Junk : public Sprite
{
public:
	static Junk *create(int junkNum,int fairyType);

	bool init(int junkNum,int fairyType);

	void update(float delta);
private:
	String* junkStr;
	float downSpeed;          //重力
	float directionSpeed;     //左右への力

	void up();
	void fadeErase(float delta);
	void erase();

};
#endif