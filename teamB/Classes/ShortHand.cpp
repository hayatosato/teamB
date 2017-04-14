#include "ShortHand.h"

bool ShortHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("newShortHand.png");

	this->setAnchorPoint(ccp(0.5, 0));

	return true;
}