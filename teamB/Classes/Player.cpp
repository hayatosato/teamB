#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

const float LongMoveDir = 6;
const float ShortMoveDir = 0.5;

bool Player::init()
{
	if (!Node::init()) return false;

	// �^�b�`�C�x���g��L���ɂ���
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
	//�O��Ƃ̃^�b�`�ʒu�̍�
	Vec2 delta = pTouch->getDelta();
	if (delta.y == 0) return;

	if (_knobFlg)
	{
		//�eLayer
		WatchLayer* watchLayer = ((WatchLayer*)(this->getParent()));

		//�擾
		float longDir = watchLayer->_longHand->getRotation();
		float shortDir = watchLayer->_shortHand->getRotation();

		//���v���
		if (delta.y > 0)
		{
			//�p�x
			longDir += LongMoveDir;
			shortDir += ShortMoveDir;
		}
		//�����v���
		else if (delta.y < 0)
		{
			//�p�x
			longDir -= LongMoveDir;
			shortDir -= ShortMoveDir;
		}

		if (longDir >= 360 || longDir <= -360) longDir -= 360;
		if (shortDir >= 360 || shortDir <= -360) shortDir += 360;

		//�X�V
		watchLayer->_longHand->setRotation(longDir);
		watchLayer->_shortHand->setRotation(shortDir);
	}
}

void Player::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_knobFlg = false;
}