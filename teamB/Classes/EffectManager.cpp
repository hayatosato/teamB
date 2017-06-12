#include "EffectManager.h"

bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;
	}



	return true;
}

void EffectManager::fairyDeath(Vec2 deathPos)
{
	DeathFairy* deathFairy = DeathFairy::create();
	deathFairy->setPosition(deathPos);
	this->addChild(deathFairy);
}