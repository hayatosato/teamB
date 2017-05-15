#include "EnemyManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//“G¶¬ŠÔŠu 3.0f
const float EnemyPopInterval = 1.0f;

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

	this->scheduleUpdate();

	return true;
}

void EnemyManager::EnemyCreater(float dt)
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> posNum(0, createPos);
	//“G¶¬
	int pos = posNum(mt);
	//Enemy* enemy = Enemy::create();
	//enemy->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPosition());
	//this->addChild(enemy);
	enemy.push_back(Enemy::create());
	enemy.at(enemy.size() - 1)->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPosition());
	this->addChild(enemy.at(enemy.size() - 1));
	
	//“G¶¬‰ñ“]—p
	//FairyNode* fairyNode = FairyNode::create(Vec2((((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPositionX()) - (designResolutionSize.width*0.5f), (((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPositionY() - (designResolutionSize.height*0.5f))));
	//fairyNode->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
	//this->addChild(fairyNode);

}

void EnemyManager::update(float delta)
{
	auto layer = ((WatchLayer*)(this->getParent()));
	ang = layer->_longHand->getRotation();
	if (ang < 0.0f)
	{
		ang = ang + 360.0f;
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		tAng = Calculation::angle(designResolutionSize*0.5f, enemy.at(i)->getPosition());
		if (tAng < 0.0f)
		{
		tAng = tAng + 360.0f;
		}

		if (ang < tAng +10.0 &&
			ang > tAng -10.0
			)
		{
			enemy.at(i)->setColor(Color3B::GREEN);
			enemy.at(i)->moveMode = true;
		}
	}
}