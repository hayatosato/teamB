#include "Shine.h"

bool Shine::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithFile("GameScene/shine.png");
	this->setScale(0.3f);
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
	this->setPositionY(this->getPositionY() + 0.25f);
}

//íœ
void Shine::erase()
{
	this->removeFromParent();
}