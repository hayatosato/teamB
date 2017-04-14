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

	initWithFile("EnemySprite.png");

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
	WatchLayer* layer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));
	if (layer->_player->_isMove) 
	{
		Hit();
	}
}

//�ړ�
void Enemy::Move(float deltaTime)
{
	//���ݒn
	Vec2 enemyPos = this->getPosition();

	//�ړ�����
	Vec2 moveDir = AttackPoint - enemyPos;
	float moveDirX = moveDir.x;
	float moveDirY = moveDir.y;
	if (moveDirX < 0) moveDirX = -moveDirX;
	if (moveDirY < 0) moveDirY = -moveDirY;

	moveDir = Vec2(moveDir.x / (moveDirX + moveDirY), moveDir.y / (moveDirX + moveDirY));

	//�ړ�
	enemyPos += moveDir * _speed * deltaTime;

	//�X�V
	this->setPosition(enemyPos);
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
		this->removeFromParentAndCleanup(true);
	}
}

//��̐j�ƓG���d�Ȃ��Ă��邩
bool Enemy::HoldCheck(Vec2 pos, Rect shortRect, Rect longRect)
{
	if (shortRect.containsPoint(pos) && longRect.containsPoint(pos))
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