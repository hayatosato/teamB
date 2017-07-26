#include "KNobEffect.h"

bool KNobEffect::init()
{
	if (!Sprite::init()) return false;

	this->initWithFile("GameScene/newKnob.png");
	this->setScale(0.5f);
	scaleBig = ScaleTo::create(1.0f,1.0f);
	fade = FadeOut::create(1.0f);
	callErase = CallFunc::create([=] { erase(); });
	spa = Spawn::create(scaleBig, fade, nullptr);
	seq = Sequence::create(spa, callErase, nullptr);

	this->runAction(seq);
}

//íœ
void KNobEffect::erase()
{
	this->removeFromParent();
}