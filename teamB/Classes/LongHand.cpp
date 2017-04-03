#include "LongHand.h"

bool LongHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("Minute hand.png");

	this->setAnchorPoint(ccp(0.5, 0));

	//“–‚½‚è”»’è‚Ì‘å‚«‚³
	_handSize = this->getContentSize();
	_handSize.width = _handSize.width / 6;

	return true;
}