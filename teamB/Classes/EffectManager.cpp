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

void EffectManager::shining(Vec2 shinPos)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> SPosX((int)shinPos.x - 20, (int)shinPos.x + 20);
	uniform_int_distribution<int> SPosY((int)shinPos.y - 30, (int)shinPos.y - 10);

	Shine* shine = Shine::create();
	shine->setPosition((float)SPosX(mt), (float)SPosY(mt));
	this->addChild(shine);

}