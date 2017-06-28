#include "SecondHand.h"

bool SecondHand::init()
{
	if (!Sprite::init()) return false;

	this->initWithFile("GameScene/bloodNeedle.png");

	this->setAnchorPoint(ccp(0.5, 0));


	return true;
}