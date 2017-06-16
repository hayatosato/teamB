#include "FairyGate.h"

bool FairyGate::init()
{
	if (!Sprite::init()) return false;
	this->initWithFile("GameScene/goodVortex.png");
	speed = 2.0f;

	this->scheduleUpdate();
	return true;
}

void FairyGate::update(float delta)
{
	if (this->getRotation() > 360)
	{
		this->setRotation(0);
	}
	this->setRotation(this->getRotation() + speed);
}