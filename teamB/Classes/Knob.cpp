#include "Knob.h"

bool Knob::init()
{
	if (!Sprite::init()) return true;

	initWithFile("GameScene/newKnob.png");

	return true;
}

void Knob::startAnimation()
{
	animation = Animation::create();

	animation->addSpriteFrameWithFileName("GameScene/newKnob.png");
	animation->addSpriteFrameWithFileName("GameScene/newKnob2.png");

	animation->setDelayPerUnit(0.3f);
	animation->setRestoreOriginalFrame(true);

	action = Animate::create(animation);
	anime = RepeatForever::create(action);
	this->runAction(anime);
}

void Knob::stopAnimation()
{
	this->stopAction(anime);
}