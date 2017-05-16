#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//�j���̊p�x
const float OneLongMoveDir = 6;
const float OneShortMoveDir = 0.5;
//�j������̊p�x
const int OneRotation = 360;
//����
const int MoveDivide = (designResolutionSize.height * 0.5f) / 80;

bool Player::init()
{
	if (!Node::init()) return false;

	downMove = 0.5f;
	maxMoveSpeed = 40.0f;
	crackCount = 0;
	
	// �^�b�`�C�x���g��L���ɂ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//�����Ă��邩
	_isMove = false;

	//this->scheduleUpdate();

	return true;
}

bool Player::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocationInView();
	touchPos.y = designResolutionSize.height - touchPos.y;

	auto layer = ((WatchLayer*)(this->getParent()));

	//�܂�Rect
	Size knobRect = layer->_knob->getContentSize();
	Vec2 knobPos  = layer->_knob->getPosition();
	//���v�K���XRect
	Size clockRect = layer->_watchSprite->getContentSize();
	Vec2 clockPos  = layer->_watchSprite->getPosition();

	//�܂ݔ���
	if (touchPos.x > (knobPos.x - knobRect.width) && touchPos.x < (knobPos.x + knobRect.width) &&
		touchPos.y > (knobPos.y - knobRect.height) && touchPos.y < (knobPos.y + knobRect.height))
	{
		//�t���O��true��
		_knobFlg = true;

		_isMove = true;
		layer->_knob->startAnimation();
	}
	//�K���X����
	if (touchPos.x >(clockPos.x - clockRect.width) && touchPos.x < (clockPos.x + clockRect.width) &&
		touchPos.y >(clockPos.y - clockRect.height) && touchPos.y < (clockPos.y + clockRect.height))
	{
		crackCount++;
	}


	return true;
}

void Player::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	//�O��Ƃ̃^�b�`�ʒu�̍�
	Vec2 delta = pTouch->getDelta();

	if (delta.y == 0) 
	{
		return;
	}
	if (_knobFlg)
	{
		//�eLayer
		WatchLayer* watchLayer = ((WatchLayer*)(this->getParent()));

		//�擾
		longDir = watchLayer->_longHand->getRotation();
		shortDir = watchLayer->_shortHand->getRotation();
		longDirF = longDir;

		//�����p�x
		longMoveDir  = OneLongMoveDir  * delta.y / MoveDivide;
		shortMoveDir = OneShortMoveDir * delta.y / MoveDivide;

		//�j�̑��x����
		if (longMoveDir > maxMoveSpeed)
		{
			longMoveDir = maxMoveSpeed;
			shortMoveDir = (maxMoveSpeed / 12.0f);
		}
		else if (longMoveDir < -maxMoveSpeed)
		{
			longMoveDir = -maxMoveSpeed;
			shortMoveDir = (-maxMoveSpeed / 12.0f);
		}
		//�p�x
		longDir += longMoveDir;
		shortDir += shortMoveDir;

		//�`�F�b�N
		if (longDir >= OneRotation) longDir -= OneRotation;
		else if (longDir <= 0.0f) longDir += OneRotation;
		if (shortDir >= OneRotation) shortDir -= OneRotation;
		else if (shortDir <= -OneRotation) shortDir += OneRotation;

		longDirF = longDir - longDirF;


		//�X�V
		watchLayer->_longHand->setRotation(longDir);
		watchLayer->_shortHand->setRotation(shortDir);
	}
}

void Player::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	//�t���O��false��
	_knobFlg = false;
	_isMove = false;
	((WatchLayer*)(this->getParent()))->_knob->stopAnimation();
}

void Player::update(float delta)
{
	//if (_isMove)
	//{
	//	//�p�x
	//	longDir += longMoveDir;
	//	shortDir += shortMoveDir;
	//	//�`�F�b�N
	//	if (longDir >= OneRotation) longDir -= OneRotation;
	//	else if (longDir <= -OneRotation) longDir += OneRotation;
	//	if (shortDir >= OneRotation) shortDir -= OneRotation;
	//	else if (shortDir <= -OneRotation) shortDir += OneRotation;
	//	//�X�V
	//	((WatchLayer*)(this->getParent()))->_longHand->setRotation(longDir);
	//	((WatchLayer*)(this->getParent()))->_shortHand->setRotation(shortDir);
	//}
	//else
	//{
	//	downSpeed();

	//	//�p�x
	//	longDir += longMoveDir;
	//	shortDir += shortMoveDir;

	//	//�`�F�b�N
	//	if (longDir >= OneRotation) longDir -= OneRotation;
	//	else if (longDir <= -OneRotation) longDir += OneRotation;
	//	if (shortDir >= OneRotation) shortDir -= OneRotation;
	//	else if (shortDir <= -OneRotation) shortDir += OneRotation;

	//	//�X�V
	//	((WatchLayer*)(this->getParent()))->_longHand->setRotation(longDir);
	//	((WatchLayer*)(this->getParent()))->_shortHand->setRotation(shortDir);
	//}

}

//�j�̃X�s�[�h��x�����鏈��
void Player::downSpeed()
{
	if (longMoveDir > 0)
	{
		longMoveDir -= downMove;
		shortMoveDir -= (downMove / 12.0f);
		if (longMoveDir <= 0)
		{
			longMoveDir = 0;
		}
		if (shortMoveDir <= 0)
		{
			shortMoveDir = 0;
		}
	}
	else
	{
		longMoveDir += downMove;
		shortMoveDir += (downMove / 12.0f);
		if (longMoveDir >= 0)
		{
			longMoveDir = 0;
		}
		if (shortMoveDir >= 0)
		{
			shortMoveDir = 0;
		}

	}

}