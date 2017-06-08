#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
#include "Player.h"
#include "MultiResolution.h"
#include "Calculation.h"

//目標地点
const Vec2 AttackPoint = designResolutionSize * 0.5f;

bool Enemy::init()
{
	if (!Sprite::init()) return false;

	initWithFile("CloseNormal.png");

	moveMode = false;
	exitNeedle = true;
	fairyModes = WAIT;

	_speed = 100;                 //動く速さ
	resetCount();                //動くまでのカウント

	//update
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	//移動
	Move(dt);

	//当たり判定
	Hit();
}

//移動
void Enemy::Move(float deltaTime)
{
	WatchLayer* watchLayer = ((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()));

	//現在地
	Vec2 enemyPos = this->getPosition();
	//移動方向
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
	//長針の上から中央に向かう
	case GO:
	{
		//移動
		enemyPos += moveDir * _speed * deltaTime;
		//更新
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_longHand->getRotation() + 90.0f));            //cocos側との角度のずれ90°

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
	//長針の上から外に向かう
	case BACK:
	{
		//移動
		enemyPos -= moveDir * _speed * deltaTime;
		//更新
		this->setPosition(enemyPos);

		if (Calculation::sq(designResolutionSize*0.5f,Vec2(watchLayer->_watchSprite->getPositionX() + ((watchLayer->_watchSprite->getContentSize().width*0.5f)*0.6f),watchLayer->_watchSprite->getPositionY())) > 
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()))
		{
			this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
				Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
				-watchLayer->_longHand->getRotation() + 90.0f));            //cocos側との角度のずれ90°
		}
		else
		{
			exitNeedle = false;
		}
	}
		break;
	//短針の上から外に向かう
	case SAVEONE:
	{
		//移動
		enemyPos -= moveDir * _speed * deltaTime;
		//更新
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_shortHand->getRotation() + 90.0f));            //cocos側との角度のずれ90°

		if (Calculation::sq(designResolutionSize*0.5f, this->getPosition()) > watchLayer->_shortHand->getContentSize().height)
		{
			fairyModes = SAVETWO;
		}

	}
	break;
	//短針の上から中央へ向かう
	case SAVETWO:
	{
		//移動
		enemyPos += moveDir * _speed * deltaTime;
		//更新
		this->setPosition(enemyPos);
		this->setPosition(Calculation::setPos(designResolutionSize*0.5f,
			Calculation::sq(designResolutionSize*0.5f, this->getPosition()),
			-watchLayer->_shortHand->getRotation() + 90.0f));            //cocos側との角度のずれ90°

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
		//float ax, ay;
		//
		//longRotate = M_PI / 180;
		//ax = enemyPos.x*cos(longRotate) - enemyPos.y*sin(longRotate);
		//ay = enemyPos.x*sin(longRotate) + enemyPos.y*cos(longRotate);

		//setPosition(Vec2(ax, ay));
	}
}

//二つの針と敵が重なっているか
bool Enemy::HoldCheck(Vec2 pos, Rect shortRect, Rect longRect)
{
	if (/*shortRect.containsPoint(pos) && */longRect.containsPoint(pos + designResolutionSize*0.5f))
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

//カウントのリセット
void Enemy::resetCount()
{
	startCount = 60;
}