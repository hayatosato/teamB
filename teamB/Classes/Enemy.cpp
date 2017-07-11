#include "Enemy.h"
#include "EnemyManager.h"
#include "WatchLayer.h"
#include "Player.h"
#include "MultiResolution.h"
#include "Calculation.h"

//�ڕW�n�_
const Vec2 AttackPoint = designResolutionSize * 0.5f;

Enemy *Enemy::create(int type)
{
	Enemy *pRet = new Enemy();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool Enemy::init(int type)
{
	if (!Sprite::init()) return false;

	typeNum = type;

	this->setScale(0.15f);

	switch (typeNum)
	{
	case 0:
	 {
		 this->initWithFile("GameScene/clockFairy1.png");
		 scorePoint = 100;
		 _speed = 100;                 //��������

		 animation = Animation::create();
		 animation->addSpriteFrameWithFileName("GameScene/clockFairy1new.png");
		 animation->addSpriteFrameWithFileName("GameScene/clockFairy2new.png");
		 animation->addSpriteFrameWithFileName("GameScene/clockFairy3new.png");
		 animation->addSpriteFrameWithFileName("GameScene/clockFairy2new.png");
		 animation->setDelayPerUnit(0.2f);
		 animation->setRestoreOriginalFrame(true);
		 action = Animate::create(animation);
		 anime = RepeatForever::create(action);
		 this->runAction(anime);
	 }
	break;
	case 1:
	 {
		 this->initWithFile("GameScene/goldFairys1.png");
		 scorePoint = 500;
		 _speed = 50;                 //��������

		 animation = Animation::create();
		 animation->addSpriteFrameWithFileName("GameScene/goldFairys1.png");
		 animation->addSpriteFrameWithFileName("GameScene/goldFairys2.png");
		 animation->addSpriteFrameWithFileName("GameScene/goldFairys3.png");
		 animation->addSpriteFrameWithFileName("GameScene/goldFairys2.png");
		 animation->setDelayPerUnit(0.2f);
		 animation->setRestoreOriginalFrame(true);
		 action = Animate::create(animation);
		 anime = RepeatForever::create(action);
		 this->runAction(anime);

	 }
	break;
	}


	bonusEffectCount = 2;
	exitNeedle = true;
	bonusFairy = false;
	fairyModes = WAIT;

	resetCount();                //�����܂ł̃J�E���g

	//update
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	//�ړ�
	Move(dt);

	if (!bonusFairy) return;
	bonusEffectCount--;
	if (bonusEffectCount < 0)
	{
		((WatchLayer*)((EnemyManager*)(this->getParent())->getParent()))->effect->chargeEffect(this->getPosition());
		bonusEffectCount = 2;
	}


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
			myCreatePos--;
			if (myCreatePos < 0)
			{
				myCreatePos = 11;
			}
			((EnemyManager*)(this->getParent()))->multipleNum[myCreatePos] -= 1;
			watchLayer->effectPlayMusic(8);
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
			if (!bonusFairy)
			{
				watchLayer->effectPlayMusic(7);
				watchLayer->plusScore((int)scorePoint*0.5f);
				watchLayer->effect->pointGet(this->getPosition(), (int)scorePoint*0.5f,bonusFairy);
			}
			bonusFairy = true;
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
	startCount = 30;
}