#include "TitleTap.h"
#include "GameScene.h"

bool TitleTap::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleTap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TitleTap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleTap::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
}

//タップした時
bool TitleTap::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, GameScene::create(), Color3B::BLACK));
	return true;
}

//タップ中
void TitleTap::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

//タップやめたとき
void TitleTap::onTouchEnded(Touch* pTouch, Event* pEvent)
{
}