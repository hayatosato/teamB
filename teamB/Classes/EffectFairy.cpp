#include "EffectFairy.h"

bool EffectFairy::init()
{
	if (!Sprite::init()) return false;

	animation = Animation::create();
	animation->addSpriteFrameWithFileName("GameScene/clockFairy1new.png");
	animation->addSpriteFrameWithFileName("GameScene/clockFairy2new.png");
	animation->addSpriteFrameWithFileName("GameScene/clockFairy3new.png");
	animation->addSpriteFrameWithFileName("GameScene/clockFairy2new.png");
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	action = Animate::create(animation);
	anime = RepeatForever::create(action);
	this->runAction(anime);



	return true;
}