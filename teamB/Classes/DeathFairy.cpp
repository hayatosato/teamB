#include "DeathFairy.h"

DeathFairy *DeathFairy::create(int actionMode,int fairyType)
{
	DeathFairy *pRet = new DeathFairy();
	if (pRet && pRet->init(actionMode,fairyType))
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


bool DeathFairy::init(int actionMode,int fairyType)
{
	if (!Sprite::init())
	{
		return false;
	}
	normalScale = 0.15f;
	this->setScale(normalScale);
	call = CallFunc::create(CC_CALLBACK_0(DeathFairy::erase, this));

	switch (fairyType)
	{
	case 0:
		this->initWithFile("GameScene/clockFairyDeath.png");
		break;
	case 1:
		this->initWithFile("GameScene/goldFairysDeath.png");
		break;
	}


	switch (actionMode)
	{
	case 0:
	{
		scale = ScaleTo::create(1.0f, 0.0f, normalScale);
		seq = Sequence::create(scale, call, nullptr);
	}
		break;
	case 1:
	{
		fadeOut = FadeOut::create(1.0f);
		seq = Sequence::create(fadeOut, call, nullptr);
	}
		break;
	default:
		break;
	}
	this->runAction(seq);

	return true;
}

void DeathFairy::erase()
{
	this->removeFromParent();
}