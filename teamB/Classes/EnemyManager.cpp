#include "EnemyManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//“G¶¬ŠÔŠu 3.0f
const float EnemyPopInterval = 0.1f;

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
	//ˆê’èŠÔ‚²‚Æ‚É“G‚ğ¶¬
	this->schedule(schedule_selector(EnemyManager::EnemyCreater), EnemyPopInterval);

	this->scheduleUpdate();

	return true;
}

//“G¶¬
void EnemyManager::EnemyCreater(float dt)
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> posNum(0, createPos);
	//“G¶¬
	pos = posNum(mt);
	if (((WatchLayer*)(this->getParent()))->breakCheck[pos] == true)
	{
		//”z—ñ‚Ì‚¸‚êC³
		pos++;
		if (pos > 11)
		{
			pos = 0;
		}

		enemy.pushBack(Enemy::create());
		enemy.at(enemy.size() - 1)->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPosition());
		this->addChild(enemy.at(enemy.size() - 1));
	}
}

void EnemyManager::update(float delta)
{
	auto layer = ((WatchLayer*)(this->getParent()));
	ang = layer->_longHand->getRotation();
	if (ang < 0.0f)
	{
		ang = ang + 360.0f;
	}
	shotAng = layer->_shortHand->getRotation();
	if (shotAng < 0.0f)
	{
		shotAng = shotAng + 360.0f;
	}
	secondAng = layer->_secondHand->getRotation();
	for (int i = 0; i < enemy.size(); i++)
	{
		tAng = Calculation::angle(designResolutionSize*0.5f, enemy.at(i)->getPosition());
		if (tAng < 0.0f)
		{
		    tAng = tAng + 360.0f;
		}
		//•ªj‚Æ—d¸‚ª“¯‚¶Šp“x‚¾‚Á‚½
		if (ang < tAng +5.0 &&
			ang > tAng -5.0 &&
			enemy.at(i)->fairyModes == enemy.at(i)->WAIT
			)
		{
			enemy.at(i)->startCount--;
		}
		else
		{
			enemy.at(i)->resetCount();
		}

		//’·j‚Æ•bj‚ÌŠp“x‚ª“¯‚¶‚É‚È‚Á‚½‚©‚Ç‚¤‚©
		if (ang < secondAng + 2.0f &&
			ang > secondAng - 2.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->GO || enemy.at(i)->fairyModes == enemy.at(i)->BACK)
			{
				enemy.at(i)->removeFromParentAndCleanup(true);
				enemy.erase(i);
			}
		}

		//’Zj‚Æ•bj‚ÌŠp“x‚ª“¯‚¶‚É‚È‚Á‚½‚©‚Ç‚¤‚©
		if (shotAng < secondAng + 2.0f &&
			shotAng > secondAng - 2.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->SAVEONE || enemy.at(i)->fairyModes == enemy.at(i)->SAVETWO)
			{
				enemy.at(i)->removeFromParentAndCleanup(true);
				enemy.erase(i);
			}
		}

	}
}