#include "LongHand.h"

bool LongHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("Minute hand.png");

	this->setAnchorPoint(ccp(0.5, 0));

	//当たり判定の大きさ
	_handSize = this->getContentSize();
	_handSize.width = _handSize.width / 6;

	return true;
}