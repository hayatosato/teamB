#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init()) return false;

	//基本位置
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//核
	_centerObj = CenterObject::create();
	_centerObj->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.8 + origin.y));
	this->addChild(_centerObj);

	//赤時計
	_redClock = RedClock::create();
	_redClock->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 1.2 + origin.y));
	_redClock->setScale(2);
	this->addChild(_redClock);

	//青時計
	_blueClock = BlueClock::create();
	_blueClock->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.4 + origin.y));
	_blueClock->setScale(2);
	this->addChild(_blueClock);

	return true;
}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{


	return true;
}