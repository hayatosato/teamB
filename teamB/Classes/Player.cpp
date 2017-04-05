#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//�j���̊p�x
const float OneLongMoveDir = 6;
const float OneShortMoveDir = 0.5;
//�j������̊p�x
const int OneRotation = 360;
//
const int MoveDivide = (designResolutionSize.height * 0.5f) / 120;

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

	//�����Ă��邩
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

	//����
	if (touchPos.x > (knobPos.x - knobRect.width) && touchPos.x < (knobPos.x + knobRect.width) &&
		touchPos.y > (knobPos.y - knobRect.height) && touchPos.y < (knobPos.y + knobRect.height))
	{
		//�t���O��true��
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

		//�����p�x
		float longMoveDir = OneLongMoveDir * delta.y / MoveDivide;
		float shortMoveDir = OneShortMoveDir * delta.y / MoveDivide;

		//�p�x
		longDir += longMoveDir;
		shortDir += shortMoveDir;

		//�`�F�b�N
		if (longDir >= OneRotation) longDir -= OneRotation;
		else if (longDir <= -OneRotation) longDir += OneRotation;
		if (shortDir >= OneRotation) shortDir -= OneRotation;
		else if (shortDir <= -OneRotation) shortDir += OneRotation;

		//�X�V
		watchLayer->_longHand->setRotation(longDir);
		watchLayer->_shortHand->setRotation(shortDir);

		//�����Ă��邩
		if(longMoveDir != 0) _isMove = true;
		else _isMove = false;
	}
}

void Player::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	//�t���O��false��
	_knobFlg = false;
	_isMove = false;
}