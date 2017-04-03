#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
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
	Hit();
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

	//����
	if (shortRect.containsPoint(enemyPos) && longRect.containsPoint(enemyPos))
	{
		this->removeFromParentAndCleanup(true);
	}
}