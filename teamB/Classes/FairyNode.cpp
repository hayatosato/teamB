#include "FairyNode.h"
#include "EnemyManager.h"
#include "WatchLayer.h"

FairyNode *FairyNode::create(Vec2 enemyPos)
{
	FairyNode *pRet = new FairyNode();
	if (pRet && pRet->init(enemyPos))
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

bool FairyNode::init(Vec2 enemyPos)
{
	if (!Node::init()) return false;

	enemy = Enemy::create();
	enemy->setPosition(enemyPos);
	this->addChild(enemy);

	this->scheduleUpdate();

	return true;
}

void FairyNode::update(float delta)
{

}