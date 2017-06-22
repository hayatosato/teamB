#include "Shine.h"

Shine *Shine::create(bool mode)
{
	Shine *pRet = new Shine();
	if (pRet && pRet->init(mode))
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

bool Shine::init(bool mode)
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithFile("GameScene/shine.png");
	numberMode = mode;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> SNum(7,14);

	Blink* blink = Blink::create(2.0f, SNum(mt));
	FadeOut* fadeDwon = FadeOut::create(2.0f);
	Spawn* spa = Spawn::create(blink, fadeDwon, nullptr);
	CallFunc* call = CallFunc::create([=]
	{
		erase();
	});
	Sequence* seq = Sequence::create(spa, DelayTime::create(2.0f), call, nullptr);
	this->runAction(seq);
	this->scheduleUpdate();
	return true;
}

void Shine::update(float delta)
{
	if (numberMode) return;
	this->setPositionY(this->getPositionY() + 0.25f);
}

//íœ
void Shine::erase()
{
	this->removeFromParent();
}