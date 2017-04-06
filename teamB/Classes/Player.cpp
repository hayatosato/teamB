#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//針一回の角度
const float OneLongMoveDir = 6;
const float OneShortMoveDir = 0.5;
//針一周分の角度
const int OneRotation = 360;
//
const int MoveDivide = (designResolutionSize.height * 0.5f) / 120;

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

	//動いているか
	_isMove = false;

	return true;
}

bool Player::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocationInView();
	touchPos.y = designResolutionSize.height - touchPos.y;

	//Rect
	Size knobRect = ((WatchLayer*)(this->getParent()))->_knob->getContentSize();
	Vec2 knobPos = ((WatchLayer*)(this->getParent()))->_knob->getPosition();

	//判定
	if (touchPos.x > (knobPos.x - knobRect.width) && touchPos.x < (knobPos.x + knobRect.width) &&
		touchPos.y > (knobPos.y - knobRect.height) && touchPos.y < (knobPos.y + knobRect.height))
	{
		//フラグをtrueに
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

		//動く角度
		float longMoveDir = OneLongMoveDir * delta.y / MoveDivide;
		float shortMoveDir = OneShortMoveDir * delta.y / MoveDivide;

		//角度
		longDir += longMoveDir;
		shortDir += shortMoveDir;

		//チェック
		if (longDir >= OneRotation) longDir -= OneRotation;
		else if (longDir <= -OneRotation) longDir += OneRotation;
		if (shortDir >= OneRotation) shortDir -= OneRotation;
		else if (shortDir <= -OneRotation) shortDir += OneRotation;

		//更新
		watchLayer->_longHand->setRotation(longDir);
		watchLayer->_shortHand->setRotation(shortDir);

		//動いているか
		if(longMoveDir != 0) _isMove = true;
		else _isMove = false;
	}
}

void Player::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	//フラグをfalseに
	_knobFlg = false;
	_isMove = false;
}