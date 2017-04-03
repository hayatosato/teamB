#include "ShortHand.h"

bool ShortHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("Short hand.png");

	this->setAnchorPoint(ccp(0.5, 0));

	//当たり判定の大きさ
	_handSize = this->getContentSize();
	_handSize.width = _handSize.width / 6;

	return true;
}