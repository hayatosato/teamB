#include "EffectManager.h"
#include "MultiResolution.h"

bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

//妖精死亡演出
void EffectManager::fairyDeath(Vec2 deathPos)
{
	DeathFairy* deathFairy = DeathFairy::create(0,0);
	deathFairy->setPosition(deathPos);
	this->addChild(deathFairy);
}

//ぴかぴかする
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

//中心からぴかぴかする
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

//妖精壁に当たり死
void EffectManager::fairyAscension(Vec2 APos,int fairyType)
{
	DeathFairy* fairyD = DeathFairy::create(1,fairyType);
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

//チャージ演出
void EffectManager::chargeEffect(Vec2 chPos)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> SPosX((int)chPos.x - 20, (int)chPos.x + 20);
	uniform_int_distribution<int> SPosY((int)chPos.y - 30, (int)chPos.y - 10);
	uniform_int_distribution<int> Color(155, 255);

	Shine* shine = Shine::create(false);
	shine->setScale(0.25f);
	shine->setPosition((float)SPosX(mt), (float)SPosY(mt));
	shine->initWithFile("GameScene/whiteShine.png");
	shine->setColor(Color3B(Color(mt), Color(mt), Color(mt)));
	this->addChild(shine, 2);
}

void EffectManager::fairyJunk(Vec2 JPos,int fairyType)
{
	Junk* junkZero = Junk::create(0,fairyType);
	Junk* junkOne =  Junk::create(1,fairyType);
	Junk* junkTwo =  Junk::create(2,fairyType);

	junkZero->setPosition(JPos);
	junkOne->setPosition(junkZero->getPositionX() + 20.0f,junkZero->getPositionY());
	junkTwo->setPosition(junkZero->getPositionX() - 20.0f, junkZero->getPositionY());

	this->addChild(junkZero,3);
	this->addChild(junkOne,2);
	this->addChild(junkTwo,2);

}

//数字の波動
void EffectManager::numWave(int num, int way)
{
	SurgeNum* surgeNum = SurgeNum::create(num, way);
	surgeNum->setPosition(designResolutionSize*0.5f);
	this->addChild(surgeNum);
}

//いくつスコアを取得したか表示
void EffectManager::pointGet(Vec2 pointPos,int point,bool bonusCheck)
{
	PointLabel* pointLabel = PointLabel::create();
	pointLabel->setPosition(pointPos);

	PointLabel* doublingLabel = PointLabel::create();
	doublingLabel->setPosition(pointPos.x + 60,pointPos.y);
	doublingLabel->setColor(Color3B::RED);

	if (bonusCheck)
	{
		pointLabel->bonusColor = true;
		String* pointStr = String::createWithFormat("%d",(int)(point*0.5f));
		pointLabel->setString(pointStr->getCString());
		String* doublingStr = String::createWithFormat("x%d", 2);
		doublingLabel->setString(doublingStr->getCString());
		doublingLabel->enableOutline(Color4B::BLACK, 2);
		this->addChild(doublingLabel);
	}
	else
	{
		String* pointStr = String::createWithFormat("%d", point);
		pointLabel->setString(pointStr->getCString());
	}

	int multipleNum = (int)point / 100;

	this->addChild(pointLabel);
}

//道中のスコア獲得について
void EffectManager::subPointGet(Vec2 subPointPos, int subPoint, bool subBonusCheck)
{
	PointLabel* pointLabel = PointLabel::create();
	pointLabel->setPosition(subPointPos);

	if (subBonusCheck)
	{
		pointLabel->bonusColor = true;
	}

	String* pointStr = String::createWithFormat("%d", subPoint);
	pointLabel->setString(pointStr->getCString());
	this->addChild(pointLabel);
}

void EffectManager::kNobTurn(Vec2 kNobPos)
{
	KNobEffect* knobEffect = KNobEffect::create();
	knobEffect->setPosition(kNobPos);
	this->addChild(knobEffect);

	KNobEffect* yaji = KNobEffect::create();
	yaji->initWithFile("GameScene/yaji.png");
	yaji->setPosition(knobEffect->getPositionX(), knobEffect->getPositionY() + 100.0f);
	this->addChild(yaji);

}

void EffectManager::yajiErase()
{

}