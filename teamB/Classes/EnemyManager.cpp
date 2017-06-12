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
	uniform_int_distribution<int> posNum(0,createPos);
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

		//“G¶¬
		enemy.pushBack(Enemy::create());
		enemy.at(enemy.size() - 1)->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(pos)->getPosition());
		this->addChild(enemy.at(enemy.size() - 1),1);
		//—d¸ŒãŒõ¶¬
		aura.pushBack(Sprite::create("GameScene/fairyAura.png"));
		aura.at(aura.size() - 1)->setPosition(enemy.at(enemy.size() - 1)->getPosition());
		aura.at(aura.size() - 1)->setScale(0.5f);
		this->addChild(aura.at(aura.size() - 1),0);
		FadeOut* fadeOut = FadeOut::create(1.0f);
		FadeIn*  fadeIn = FadeIn::create(1.0f);
		Sequence* seq = Sequence::create(fadeOut, fadeIn, nullptr);
		RepeatForever* rep = RepeatForever::create(seq);
		aura.at(aura.size() - 1)->runAction(rep);
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
				deleteEnemy(i,true);
			}
		}

		//’Zj‚Æ•bj‚ÌŠp“x‚ª“¯‚¶‚É‚È‚Á‚½‚©‚Ç‚¤‚©
		if (shotAng < secondAng + 2.0f &&
			shotAng > secondAng - 2.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->SAVEONE || enemy.at(i)->fairyModes == enemy.at(i)->SAVETWO)
			{
				deleteEnemy(i,true);
			}
		}

		//—d¸‚ªj‚ÌS‘©‚©‚çŠO‚ê‚½‚çƒQ[ƒg‚Æ‚ÌŠp“x·‚ğ‹‚ß‹ß‚©‚Á‚½‚çˆ—‚ğ‚µÅŒã‚É—d¸‚ğíœ‚·‚é
		if (enemy.at(i)->exitNeedle == false)
		{
			for (int a = 0; a < layer->fairyGate.size(); a++)
			{
				//ƒQ[ƒg‚ÌŠp“xæ“¾
				fairyGateAng = Calculation::angle(designResolutionSize*0.5, layer->fairyGate.at(a)->getPosition());
				if (fairyGateAng < 0.0f)
				{
					fairyGateAng += 360.0f;
				}
				//ƒQ[ƒg‚ÌŠp“x‚Æ—d¸‚ÌŠp“x‚ª“¯‚¶‚¾‚Á‚½‚Æ‚«ƒQ[ƒg‚Ìó‘Ô‚ğ•\¦
				if (tAng < fairyGateAng + 2.0f &&
					tAng > fairyGateAng - 2.0f)
				{
					int GateNum = a;
					GateNum--;
					if (GateNum < 0) GateNum = 11;
					if (layer->breakCheck[GateNum] == false)
					{
						layer->repairNumber(GateNum);
					}
				}

			}
			deleteEnemy(i,false);
		}

		aura.at(i)->setPosition(enemy.at(i)->getPosition());

	}
}

void EnemyManager::deleteEnemy(int enemyNum,bool death)
{
	if (death)
	{
		((WatchLayer*)(this->getParent()))->effect->fairyDeath(enemy.at(enemyNum)->getPosition());
	}

	enemy.at(enemyNum)->removeFromParentAndCleanup(true);
	enemy.erase(enemyNum);
	aura.at(enemyNum)->removeFromParentAndCleanup(true);
	aura.erase(enemyNum);
}