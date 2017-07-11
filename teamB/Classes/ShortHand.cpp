#include "ShortHand.h"

bool ShortHand::init()
{
	if (!Sprite::init()) return false;

	initWithFile("GameScene/newShortHand.png");

	this->setAnchorPoint(ccp(0.5, 0));

	bonusShine = Sprite::create("GameScene/bonusShine.png");
	bonusShine->setScale(0.3f);
	this->addChild(bonusShine);

	this->scheduleUpdate();

	return true;
}

void ShortHand::update(float delta)
{
	bonusShine->setPosition(Vec2(this->getPositionX() - 330.0f, this->getPositionY() - 310.0f));
	bonusShine->setRotation(bonusShine->getRotation() + 5);
	if (bonusShine->getRotation() > 360.0f)
	{
		bonusShine->setRotation(0.0f);
	}
}