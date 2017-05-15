#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
#include "Player.h"
#include "MultiResolution.h"

//�ڕW�n�_
const Vec2 AttackPoint = designResolutionSize * 0.5f;

bool Enemy::init()
{
	if (!Sprite::init()) return false;

	initWithFile("CloseNormal.png");

	moveMode = false;

	_speed = 100;

	//update
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	//�ړ�
	Move(dt);

	//�����蔻��
		Hit();
}

//�ړ�
void Enemy::Move(float deltaTime)
{
	if (moveMode)
	{
		//���ݒn
		Vec2 enemyPos = this->getPosition();

		//�ړ�����
		Vec2 moveDir = AttackPoint - enemyPos;

		moveDir.normalize();

		//�ړ�
		enemyPos += moveDir * _speed * deltaTime;

		//�X�V
		this->setPosition(enemyPos);
	}
}

//�����蔻��
void Enemy::Hit()
{
	//�e�I�u�W�F�N�g
	WatchLayer* watchLayer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));

	//Rect
	Vec2 enemyPos = this->getPosition();
	Rect shortRect = watchLayer->_shortHand->getBoundingBox();
	Rect longRect = watchLayer->_longHand->getBoundingBox();

	//Rotate
	float shortRotate = watchLayer->_shortHand->getRotation();
	float longRotate = watchLayer->_longHand->getRotation();

	//����
	if (HoldCheck(enemyPos, shortRect, longRect) /*&&
		JastHandCheck(shortRotate, longRotate)*/)
	{
		//float ax, ay;
		//
		//longRotate = M_PI / 180;
		//ax = enemyPos.x*cos(longRotate) - enemyPos.y*sin(longRotate);
		//ay = enemyPos.x*sin(longRotate) + enemyPos.y*cos(longRotate);

		//setPosition(Vec2(ax, ay));



	}
}

//��̐j�ƓG���d�Ȃ��Ă��邩
bool Enemy::HoldCheck(Vec2 pos, Rect shortRect, Rect longRect)
{
	if (/*shortRect.containsPoint(pos) && */longRect.containsPoint(pos + designResolutionSize*0.5f))
	{
		return true;
	}

	return false;
}

//�j���d�Ȃ��Ă��Ȃ���
bool Enemy::JastHandCheck(float shortRotate, float longRotate)
{
	//��
	const float Difference = 10.0f;
	float handDif = shortRotate - longRotate;

	if (handDif < -Difference || handDif > Difference)
	{
		return true;
	}

	return false;
}