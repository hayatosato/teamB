#include "Junk.h"

Junk *Junk::create(int junkNum,int fairyType)
{
	Junk *pRet = new Junk();
	if (pRet && pRet->init(junkNum,fairyType))
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

bool Junk::init(int junkNum,int fairyType)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (fairyType)
	{
	case 0:
		junkStr = String::createWithFormat("GameScene/JunkParts%d.png", junkNum);
		break;
	case 1:
		junkStr = String::createWithFormat("GameScene/JunkPartsGold%d.png", junkNum);
		break;
	case 2:
		junkStr = String::createWithFormat("GameScene/JunkPartsSilver%d.png", junkNum);
		break;
	}

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
	uniform_int_distribution<int> dPower(-400,400);
	uniform_int_distribution<int> JPower(300,400);


	downSpeed = (float)JPower(mt)*0.01f;
	directionSpeed = (float)dPower(mt)*0.01;
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