#include "UIManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"
#include "Calculation.h"

bool UIManager::init()
{
	if (!Node::init()) return false;

	scoreBasePos = Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*0.9f);

	score = 0;

	gauge = Sprite::create("GameScene/timeWaku.png");
	gauge->setPosition(scoreBasePos);
	this->addChild(gauge);

	scoreBoard = Sprite::create("GameScene/scoreIta.png");
	scoreBoard->setPosition(gauge->getPositionX() - 70, gauge->getPositionY()+(gauge->getContentSize().height*0.5f));
	this->addChild(scoreBoard);

	scoreLabel = Label::createWithTTF("1", "fonts/PixelMplus12-Bold.ttf",80);
	String* scoreStr = String::createWithFormat("%06d",score);
	scoreLabel->setString(scoreStr->getCString());
	scoreLabel->setPosition(scoreBasePos);
	scoreLabel->setColor(Color3B::BLACK);
	this->addChild(scoreLabel, 3);


	this->scheduleUpdate();
	return true;
}

void UIManager::update(float delta)
{
	String* scoreStr = String::createWithFormat("%06d", score);
	scoreLabel->setString(scoreStr->getCString());
}