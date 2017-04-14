#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
#include "Player.h"
#include "MultiResolution.h"

//目標地点
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
	//移動
	Move(dt);

	//当たり判定
	WatchLayer* layer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));
	if (layer->_player->_isMove) 
	{
		Hit();
	}
}

//移動
void Enemy::Move(float deltaTime)
{
	//現在地
	Vec2 enemyPos = this->getPosition();

	//移動方向
	Vec2 moveDir = AttackPoint - enemyPos;
	float moveDirX = moveDir.x;
	float moveDirY = moveDir.y;
	if (moveDirX < 0) moveDirX = -moveDirX;
	if (moveDirY < 0) moveDirY = -moveDirY;

	moveDir = Vec2(moveDir.x / (moveDirX + moveDirY), moveDir.y / (moveDirX + moveDirY));

	//移動
	enemyPos += moveDir * _speed * deltaTime;

	//更新
	this->setPosition(enemyPos);
}

//当たり判定
void Enemy::Hit()
{
	//親オブジェクト
	WatchLayer* watchLayer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));

	//Rect
	Vec2 enemyPos = this->getPosition();
	Rect shortRect = watchLayer->_shortHand->getBoundingBox();
	Rect longRect = watchLayer->_longHand->getBoundingBox();

	//Rotate
	float shortRotate = watchLayer->_shortHand->getRotation();
	float longRotate = watchLayer->_longHand->getRotation();

	//判定
	if (HoldCheck(enemyPos, shortRect, longRect) /*&&
		JastHandCheck(shortRotate, longRotate)*/)
	{
		this->removeFromParentAndCleanup(true);
	}
}

//二つの針と敵が重なっているか
bool Enemy::HoldCheck(Vec2 pos, Rect shortRect, Rect longRect)
{
	if (shortRect.containsPoint(pos) && longRect.containsPoint(pos))
	{
		return true;
	}

	return false;
}

//針が重なっていないか
bool Enemy::JastHandCheck(float shortRotate, float longRotate)
{
	//差
	const float Difference = 10.0f;
	float handDif = shortRotate - longRotate;

	if (handDif < -Difference || handDif > Difference)
	{
		return true;
	}

	return false;
}