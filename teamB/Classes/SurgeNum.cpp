#include "SurgeNum.h"

SurgeNum *SurgeNum::create(int num, int way)
{
	SurgeNum *pRet = new SurgeNum();
	if (pRet && pRet->init(num,way))
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

bool SurgeNum::init(int num, int way)
{
	if (!Sprite::init()) return false;

	this->setScale(0.6f);

	String* wayNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num, way);
	this->initWithFile(wayNum->getCString());

	FadeOut* fadeOut = FadeOut::create(0.5f);
	CallFunc* callErase = CallFunc::create([=] {
		erase();
	});
	Sequence* seq = Sequence::create(fadeOut, callErase, nullptr);
	this->runAction(seq);


	this->scheduleUpdate();
	return true;
}

void SurgeNum::update(float delta)
{
	this->setScale(this->getScale() + 0.005f);
}

void SurgeNum::erase()
{
	this->removeFromParent();
}