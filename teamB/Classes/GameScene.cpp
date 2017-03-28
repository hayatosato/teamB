#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init()) return false;

	//��{�ʒu
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�j
	_centerObj = CenterObject::create();
	_centerObj->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.8 + origin.y));
	this->addChild(_centerObj);

	//�Ԏ��v
	_redClock = RedClock::create();
	_redClock->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 1.2 + origin.y));
	_redClock->setScale(2);
	this->addChild(_redClock);

	//���v
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