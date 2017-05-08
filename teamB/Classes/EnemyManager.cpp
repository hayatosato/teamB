#include "EnemyManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//“G¶¬ŠÔŠu
const float EnemyPopInterval = 3.0f;

EnemyManager *EnemyManager::create(int formPosNum)
{
	EnemyManager *pRet = new EnemyManager();
	if (pRet && pRet->init(formPosNum))
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


bool EnemyManager::init(int formPosNum)
{
	if (!Node::init()) return false;

	createPos = formPosNum;
	//update
	this->schedule(schedule_selector(EnemyManager::EnemyCreater), EnemyPopInterval);

	return true;
}

void EnemyManager::EnemyCreater(float dt)
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> posNum(0, createPos);
	//uniform_int_distribution<int> createUpDown(0, 1);
	//uniform_int_distribution<int> createPosX(0, 10);

	////“G¶¬‚ÌˆÊ’u
	//Vec2 enemyPos = designResolutionSize * 0.5f;
	//if (createUpDown(mt) == 0) enemyPos.y += designResolutionSize.height * 0.6f;
	//else enemyPos.y -= designResolutionSize.height * 0.6f;
	//enemyPos.x = designResolutionSize.width * createPosX(mt) * 0.1f;

	//“G¶¬
	Enemy* enemy = Enemy::create();
	enemy->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(posNum(mt))->getPosition());
	//enemy->setScale(0.3f);
	this->addChild(enemy);
}