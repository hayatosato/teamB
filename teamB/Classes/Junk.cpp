#include "Junk.h"

Junk *Junk::create(int junkNum)
{
	Junk *pRet = new Junk();
	if (pRet && pRet->init(junkNum))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Junk::init(int junkNum)
{
	if (!Sprite::init())
	{
		return false;
	}
	String* junkStr = String::createWithFormat("GameScene/JunkParts%d.png", junkNum);
	this->initWithFile(junkStr->getCString());
	this->setScale(0.15f);

	this->scheduleOnce(schedule_selector(Junk::fadeErase), 0.5f);

	downSpeed = 0;
	directionSpeed = 0;
	this->scheduleUpdate();

	up();

	return true;
}

void Junk::update(float delta)
{
	downSpeed -= 0.2f;
	if (directionSpeed > 0)
	{
		directionSpeed -= 0.2f;
	}
	else if(directionSpeed < 0)
	{
		directionSpeed += 0.2f;
	}
	this->setPosition(this->getPositionX() + directionSpeed,this->getPositionY() + downSpeed);
}

void Junk::up()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dPower(-4,4);

	downSpeed = 3.0f;
	directionSpeed = (float)dPower(mt);
}

void Junk::erase()
{
	this->removeFromParent();
}

void Junk::fadeErase(float delta)
{
	FadeOut* fade = FadeOut::create(0.5f);
	CallFunc* callErase = CallFunc::create([=] 
	{
		erase();
	});
	Sequence* seq = Sequence::create(fade, callErase, nullptr);
	this->runAction(seq);
}