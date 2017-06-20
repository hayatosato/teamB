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
	for (int j = 0; j < 5; j++)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> SPosX((int)shinPos.x - 20, (int)shinPos.x + 20);
		uniform_int_distribution<int> SPosY((int)shinPos.y - 30, (int)shinPos.y - 10);

		Shine* shine = Shine::create();
		shine->setScale(0.25f);
		shine->setPosition((float)SPosX(mt), (float)SPosY(mt));
		this->addChild(shine);
	}
}

void EffectManager::numberShining(Vec2 numSPos)
{
	for (int i = 0; i < 20; i++)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> SPosX((int)numSPos.x - 200, (int)numSPos.x + 200);
		uniform_int_distribution<int> SPosY((int)numSPos.y - 200, (int)numSPos.y + 200);

		Shine* shine = Shine::create();
		shine->setScale(0.5f);
		shine->numberMode = true;
		shine->setPosition(numSPos);
		this->addChild(shine);
		shine->runAction(MoveTo::create(2.0f, Vec2(SPosX(mt), SPosY(mt))));
	}
}