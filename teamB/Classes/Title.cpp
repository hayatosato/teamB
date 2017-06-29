#include "Title.h"
#include "WatchLayer.h"

bool Title::init()
{
	if (!Sprite::init()) return false;
	this->initWithFile("GameScene/ferock2.png");
	this->setScale(0.9f);
	speed = 0.0f;
	titleGravity = false;

	this->scheduleUpdate();
	return true;
}

void Title::update(float delta)
{
	if (!titleGravity) return;
	speed += 0.5f;
	this->setPositionY(this->getPositionY() + speed);
}

//ƒ`ƒ‡ƒC‰º‚Ö
void Title::upStart()
{
	titleGravity = true;
	speed -= 5.0f;
	((WatchLayer*)(this->getParent()))->navi->removeFromParent();
	FadeOut* bOut = FadeOut::create(0.7f);
	((WatchLayer*)(this->getParent()))->blackBack->runAction(bOut);
	this->scheduleOnce(schedule_selector(Title::delayWatchStart), 1.5f);
}

void Title::delayWatchStart(float delta)
{
	((WatchLayer*)(this->getParent()))->startCountDown();
	this->removeFromParent();
}