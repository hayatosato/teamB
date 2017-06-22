#include "EffectManager.h"

bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

//ódê∏éÄñSââèo
void EffectManager::fairyDeath(Vec2 deathPos)
{
	DeathFairy* deathFairy = DeathFairy::create(0);
	deathFairy->setPosition(deathPos);
	this->addChild(deathFairy);
}

//Ç“Ç©Ç“Ç©Ç∑ÇÈ
void EffectManager::shining(Vec2 shinPos)
{
	for (int j = 0; j < 5; j++)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> SPosX((int)shinPos.x - 20, (int)shinPos.x + 20);
		uniform_int_distribution<int> SPosY((int)shinPos.y - 30, (int)shinPos.y - 10);

		Shine* shine = Shine::create(false);
		shine->setScale(0.25f);
		shine->setPosition((float)SPosX(mt), (float)SPosY(mt));
		this->addChild(shine);
	}
}

//íÜêSÇ©ÇÁÇ“Ç©Ç“Ç©Ç∑ÇÈ
void EffectManager::numberShining(Vec2 numSPos)
{
	for (int i = 0; i < 20; i++)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> SPosX((int)numSPos.x - 200, (int)numSPos.x + 200);
		uniform_int_distribution<int> SPosY((int)numSPos.y - 200, (int)numSPos.y + 200);

		Shine* shine = Shine::create(true);
		shine->setScale(0.4f);
		shine->setPosition(numSPos);
		this->addChild(shine);
		shine->runAction(MoveTo::create(2.0f, Vec2(SPosX(mt), SPosY(mt))));
	}
}

//ódê∏ï«Ç…ìñÇΩÇËéÄ
void EffectManager::fairyAscension(Vec2 APos)
{
	DeathFairy* fairyD = DeathFairy::create(1);
	fairyD->setPosition(APos);
	this->addChild(fairyD,1);

	for (int j = 0; j < 10; j++)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> SPosX((int)APos.x - 40, (int)APos.x + 40);
		uniform_int_distribution<int> SPosY((int)APos.y - 20, (int)APos.y - 10);

		Shine* shine = Shine::create(false);
		shine->setScale(0.25f);
		shine->setPosition((float)SPosX(mt), (float)SPosY(mt));
		shine->initWithFile("GameScene/whiteShine.png");
		this->addChild(shine,2);
	}

}