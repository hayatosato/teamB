#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

const float LongMoveDir = 6;
const float ShortMoveDir = 0.5;

bool Player::init()
{
	if (!Node::init()) return false;

	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Player::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocationInView();
	touchPos.y = designResolutionSize.height - touchPos.y;

	//Rect
	//Rect knobRect = ((WatchLayer*)(this->getParent()))->_knob->getBoundingBox();
	Size knobRect = ((WatchLayer*)(this->getParent()))->_knob->getContentSize();
	Vec2 knobPos = ((WatchLayer*)(this->getParent()))->_knob->getPosition();

	log("knob X:%f, Y:%f", knobPos.x, knobPos.y);
	log("touch X:%f, Y:%f", touchPos.x, touchPos.y);

	//
	//if (knobRect.containsPoint(touchPos))
	//{
	//	_knobFlg = true;
	//}
	if (touchPos.x > (knobPos.x - knobRect.width) && touchPos.x < (knobPos.x + knobRect.width) &&
		touchPos.y > (knobPos.y - knobRect.height) && touchPos.y < (knobPos.y + knobRect.height))
	{
		_knobFlg = true;
	}

	return true;
}

void Player::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	//前回とのタッチ位置の差
	Vec2 delta = pTouch->getDelta();
	if (delta.y == 0) return;

	if (_knobFlg)
	{
		//親Layer
		WatchLayer* watchLayer = ((WatchLayer*)(this->getParent()));

		//取得
		float longDir = watchLayer->_longHand->getRotation();
		float shortDir = watchLayer->_shortHand->getRotation();

		//時計回り
		if (delta.y > 0)
		{
			//角度
			longDir += LongMoveDir;
			shortDir += ShortMoveDir;
		}
		//反時計回り
		else if (delta.y < 0)
		{
			//角度
			longDir -= LongMoveDir;
			shortDir -= ShortMoveDir;
		}

		if (longDir >= 360 || longDir <= -360) longDir -= 360;
		if (shortDir >= 360 || shortDir <= -360) shortDir += 360;

		//更新
		watchLayer->_longHand->setRotation(longDir);
		watchLayer->_shortHand->setRotation(shortDir);
	}
}

void Player::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_knobFlg = false;
}