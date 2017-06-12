#include "DeathFairy.h"

bool DeathFairy::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	normalScale = 0.15f;

	this->initWithFile("GameScene/clockFairyDeath.png");
	this->setScale(normalScale);

	scale = ScaleTo::create(1.0f, 0.0f, normalScale);
	call = CallFunc::create(CC_CALLBACK_0(DeathFairy::erase, this));
	seq = Sequence::create(scale, call, nullptr);



	this->runAction(seq);




	return true;
}

void DeathFairy::erase()
{
	this->removeFromParent();
}