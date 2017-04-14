#include "LongHand.h"

bool LongHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("newMinuteHand2.png");

	this->setAnchorPoint(ccp(0.5, 0));

	return true;
}