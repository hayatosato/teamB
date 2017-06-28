#include "Player.h"
#include "WatchLayer.h"
#include "MultiResolution.h"
#include "Calculation.h"

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

	masterTap = false;
	downMove     = 0.5f;
	maxMoveSpeed = 5.0f;
	
	// �^�b�`�C�x���g��L���ɂ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//�����Ă��邩
	_isMove = false;

	this->scheduleUpdate();

	return true;
}

bool Player::onTouchBegan(Touch* pTouch, Event* pEvent)
{

	Vec2 touchPos = pTouch->getLocationInView();
	touchPos.y = designResolutionSize.height - touchPos.y;

	auto layer = ((WatchLayer*)(this->getParent()));

	layer->start(); //���������߂̉��}���u

	//�܂�Rect
	Size knobRect = layer->_knob->getContentSize();
	Vec2 knobPos  = layer->_knob->getPosition();
	//���v�K���XRect
	Size clockRect = layer->_watchSprite->getContentSize();
	Vec2 clockPos  = layer->_watchSprite->getPosition();

	//�܂ݔ���
	if (touchPos.x > (knobPos.x - knobRect.width) && touchPos.x < (knobPos.x + knobRect.width) &&
		touchPos.y > (knobPos.y - knobRect.height) && touchPos.y < (knobPos.y + knobRect.height)&&
		masterTap)
	{
		//�t���O��true��
		_knobFlg = true;

		_isMove = true;
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
		else if (shortDir <= -0.0f) shortDir += OneRotation;

		longDirF = longDir - shortDir;
		if (longDirF < -175.0f && longDirF > -185.0f ||
			longDirF > 175.0f  && longDirF < 185.0f)
		{
			watchLayer->_longHand->setColor(Color3B::GREEN);
			watchLayer->_shortHand->setColor(Color3B::GREEN);
			parallel = true;
		}
		else
		{
			watchLayer->_longHand->setColor(Color3B::WHITE);
			watchLayer->_shortHand->setColor(Color3B::WHITE);
			parallel = false;
		}

		//�܂݂��񂷏���
		if (watchLayer->_longHand->getRotation() - longDir < 1.0f &&
			watchLayer->_longHand->getRotation() - longDir > -1.0f)
		{
			if (watchLayer->_knob->numberOfRunningActions() != 0)
			{
				watchLayer->_knob->stopAnimation();
			}
		}
		else
		{
			if (watchLayer->_knob->numberOfRunningActions() == 0)
			{
				watchLayer->_knob->startAnimation();
			}
		}
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
	if (((WatchLayer*)(this->getParent()))->_knob->numberOfRunningActions() != 0)
	{
		((WatchLayer*)(this->getParent()))->_knob->stopAnimation();
	}
}

void Player::update(float delta)
{
	auto layer = ((WatchLayer*)(this->getParent()));
	int gateCount = 0;  //�S�[���ł��邩���f�Ɏg�p
	for (int i = 0; i < layer->fairyGate.size(); i++)
	{
		float gatePlus = Calculation::angle(designResolutionSize*0.5, layer->fairyGate.at(i)->getPosition()) + 5.0f;
		float gateMinus= Calculation::angle(designResolutionSize*0.5, layer->fairyGate.at(i)->getPosition()) - 5.0f;
		if (gateMinus < 0.0f) gateMinus += 360.0f;
		if (i == 0)
		{
			if (longDir < gatePlus ||
				longDir > gateMinus)
			{
				gateCount++;
			}
		}
		else
		{
			if (longDir < gatePlus &&
				longDir > gateMinus)
			{
				gateCount++;
			}
		}
	}
	if (gateCount == 0)
	{
		layer->_longHand->road->setVisible(false);
	}
	else
	{
		layer->_longHand->road->setVisible(true);
	}


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