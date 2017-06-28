#include "LongHand.h"
#include "MultiResolution.h"

bool LongHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("GameScene/newMinuteHand2.png");

	this->setAnchorPoint(ccp(0.5, 0));

	this->scheduleUpdate();

	//Œõ‚Ì“¹
	road = Sprite::create("GameScene/road.png");
	road->setScale(0.4f);
	this->addChild(road);

	return true;
}

void LongHand::update(float delta)
{
	road->setPosition(Vec2(this->getPositionX() - 330.0f,this->getPositionY() - 230.0f));
}