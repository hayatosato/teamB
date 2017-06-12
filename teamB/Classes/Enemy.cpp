#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
#include "Player.h"
#include "MultiResolution.h"
#include "Calculation.h"

//�ڕW�n�_
const Vec2 AttackPoint = designResolutionSize * 0.5f;

bool Enemy::init()
{
	if (!Sprite::init()) return false;

	initWithFile("CloseNormal.png");

	moveMode   = false;
	exitNeedle = true;
	fairyModes = WAIT;

	_speed = 100;                 //��������
	resetCount();                //�����܂ł̃J�E���g

	//update
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	//�ړ�
	Move(dt);
}

//�ړ�
void Enemy::Move(float deltaTime)
{
	WatchLayer* watchLayer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));

	//���ݒn
	Vec2 enemyPos = this->getPosition();
	//�ړ�����
	Vec2 moveDir = AttackPoint - enemyPos;
	moveDir.normalize();

	switch (fairyModes)
	{
	case WAIT:
	{
		if (startCount <= 0)
		{
			this->setColor(Color3B::GREEN);
			fairyModes = GO;
		}
	}
		break;
	//���j�̏ォ�璆���Ɍ�����
	case GO:
	{
		//�ړ�
		enemyPos += moveDir * _speed * deltaTime;
		//�X�V
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_longHand->getRotation() + 90.0f));            //cocos���Ƃ̊p�x�̂���90��

		if (this->getPositionX() > designResolutionSize.width*0.49f &&
			this->getPositionX() < designResolutionSize.width*0.51f &&
			this->getPositionY() > designResolutionSize.height*0.49f&&
			this->getPositionY() < designResolutionSize.height*0.51f)
		{
			if (watchLayer->_player->parallel == true)
			{
				fairyModes = SAVEONE;
			}
			else
			{
				fairyModes = BACK;
			}
		}
	}
		break;
	//���j�̏ォ��O�Ɍ�����
	case BACK:
	{
		//�ړ�
		enemyPos -= moveDir * _speed * deltaTime;
		//�X�V
		this->setPosition(enemyPos);

		if (Calculation::sq(designResolutionSize*0.5f,Vec2(watchLayer->_watchSprite->getPositionX() + ((watchLayer->_watchSprite->getContentSize().width*0.5f)*0.6f),watchLayer->_watchSprite->getPositionY())) > 
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()))
		{
			this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
				Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
				-watchLayer->_longHand->getRotation() + 90.0f));            //cocos���Ƃ̊p�x�̂���90��
		}
		else
		{
			exitNeedle = false;
		}
	}
		break;
	//�Z�j�̏ォ��O�Ɍ�����
	case SAVEONE:
	{
		//�ړ�
		enemyPos -= moveDir * _speed * deltaTime;
		//�X�V
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_shortHand->getRotation() + 90.0f));            //cocos���Ƃ̊p�x�̂���90��

		if (Calculation::sq(designResolutionSize*0.5f, this->getPosition()) > watchLayer->_shortHand->getContentSize().height)
		{
			fairyModes = SAVETWO;
		}

	}
	break;
	//�Z�j�̏ォ�璆���֌�����
	case SAVETWO:
	{
		//�ړ�
		enemyPos += moveDir * _speed * deltaTime;
		//�X�V
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_shortHand->getRotation() + 90.0f));            //cocos���Ƃ̊p�x�̂���90��

		if (this->getPositionX() > designResolutionSize.width*0.49f &&
			this->getPositionX() < designResolutionSize.width*0.51f &&
			this->getPositionY() > designResolutionSize.height*0.49f&&
			this->getPositionY() < designResolutionSize.height*0.51f)
		{
			if (watchLayer->_player->parallel == true)
			{
				fairyModes = BACK;
			}
			else
			{
				fairyModes = SAVEONE;
			}
		}
	}
	break;
	default:
		break;
	}
}

//�J�E���g�̃��Z�b�g
void Enemy::resetCount()
{
	startCount = 60;
}