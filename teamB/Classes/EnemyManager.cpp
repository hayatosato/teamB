#include "EnemyManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//敵生成間隔 3.0f
const float EnemyPopInterval = 4.0f;

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

	masterFairy = false;

	createPos = formPosNum;
	wallCount = 0;
	for (int i = 0; i < 12; i++)
	{
		multipleNum[i] = 0;
	}
	//一定時間ごとに敵を生成
	this->schedule(schedule_selector(EnemyManager::EnemyCreater), EnemyPopInterval);

	this->scheduleUpdate();

	return true;
}

//敵生成
void EnemyManager::EnemyCreater(float dt)
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> posNum(0,createPos);
	//敵生成
	pos = posNum(mt);
	if (((WatchLayer*)(this->getParent()))->breakCheck[pos] == true &&
		multipleNum[pos] == 0  &&
		enemy.size() < 10 &&
		masterFairy)
	{
		multipleNum[pos] += 1;
		//配列のずれ修正
		pos++;
		if (pos > 11)
		{
			pos = 0;
		}
		((WatchLayer*)(this->getParent()))->adventGateMotion(pos);
	}
}

void EnemyManager::fairyCreate(int fairyCreatePos)
{
	//敵生成
	enemy.pushBack(Enemy::create(fairyAdvent()));
	enemy.at(enemy.size() - 1)->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(fairyCreatePos)->getPosition());
	enemy.at(enemy.size() - 1)->myCreatePos = pos;
	this->addChild(enemy.at(enemy.size() - 1), 1);
	//妖精後光生成
	aura.pushBack(Sprite::create("GameScene/fairyAura.png"));
	aura.at(aura.size() - 1)->setPosition(enemy.at(enemy.size() - 1)->getPosition());
	aura.at(aura.size() - 1)->setScale(0.5f);
	this->addChild(aura.at(aura.size() - 1), 0);
	FadeOut* fadeOut = FadeOut::create(1.0f);
	FadeIn*  fadeIn = FadeIn::create(1.0f);
	Sequence* seq = Sequence::create(fadeOut, fadeIn, nullptr);
	RepeatForever* rep = RepeatForever::create(seq);
	aura.at(aura.size() - 1)->runAction(rep);

}

void EnemyManager::update(float delta)
{
	auto layer = ((WatchLayer*)(this->getParent()));
	//長針の角度
	ang = layer->_longHand->getRotation();
	if (ang < 0.0f)
	{
		ang = ang + 360.0f;
	}
	//短針の角度
	shotAng = layer->_shortHand->getRotation();
	if (shotAng < 0.0f)
	{
		shotAng = shotAng + 360.0f;
	}
	//秒針の角度
	secondAng = layer->_secondHand->getRotation();
	for (int i = 0; i < enemy.size(); i++)
	{
		tAng = Calculation::angle(designResolutionSize*0.5f, enemy.at(i)->getPosition());
		if (tAng < 0.0f)
		{
		    tAng = tAng + 360.0f;
		}
		float tAngPlus = tAng + 5.0f;
		float tAngMinus = tAng - 5.0f;
		if (tAngMinus <= 0)
		{
			tAngMinus += 360.0f;
		}
		//分針と妖精が同じ角度だった時
		if (ang < tAngPlus &&
			ang > tAngMinus &&
			enemy.at(i)->fairyModes == enemy.at(i)->WAIT
			)
		{
			enemy.at(i)->startCount--;
		}
		else
		{
			//12時の角度調整
			if (tAng == 0.0f)
			{
				if (ang < tAngPlus && enemy.at(i)->fairyModes == enemy.at(i)->WAIT ||
					ang > tAngMinus &&enemy.at(i)->fairyModes == enemy.at(i)->WAIT)
				{
					enemy.at(i)->startCount--;
					continue;
				}
			}
			enemy.at(i)->resetCount();
		}

		//長針と秒針の角度が同じになったかどうか
		if (ang < secondAng + 3.0f &&
			ang > secondAng - 3.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->GO || enemy.at(i)->fairyModes == enemy.at(i)->BACK)
			{
				deleteEnemy(i,true);
				return;
			}
		}

		//短針と秒針の角度が同じになったかどうか
		if (shotAng < secondAng + 3.0f &&
			shotAng > secondAng - 3.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->SAVEONE || enemy.at(i)->fairyModes == enemy.at(i)->SAVETWO)
			{
				deleteEnemy(i,true);
				return;
			}
		}

		//妖精が針の拘束から外れたらゲートとの角度差を求め近かったら処理をし最後に妖精を削除する
		if (enemy.at(i)->exitNeedle == false)
		{
			for (int a = 0; a < layer->fairyGate.size(); a++)
			{
				//ゲートの角度取得
				fairyGateAng = Calculation::angle(designResolutionSize*0.5, layer->fairyGate.at(a)->getPosition());
				float fairyGateAngPlus = fairyGateAng + 5.0f;
				float fairyGateAngMinus = fairyGateAng - 5.0f;
				if (fairyGateAngMinus <= 0)
				{
					fairyGateAngMinus += 360.0f;
				}
				int GateNum = a;
				GateNum--;
				if (GateNum < 0) GateNum = 11;

				//ゲートの角度と妖精の角度が同じだったときゲートの状態を表示
				if (tAng < fairyGateAngPlus &&
					tAng > fairyGateAngMinus)
				{
					if (layer->breakCheck[GateNum] == false)
					{
						layer->effect->shining(layer->fairyGate.at(a)->getPosition());
						layer->repairNumber(GateNum,enemy.at(i)->bonusFairy,enemy.at(i)->scorePoint,enemy.at(i)->getPosition());
						wallCount++;
					}
				}
				else if (fairyGateAng == 0.0f)
				{
					if (layer->breakCheck[GateNum] == false)
					{
						if (tAng < fairyGateAngPlus ||
							tAng > fairyGateAngMinus)
						{
						    layer->effect->shining(layer->fairyGate.at(a)->getPosition());
							layer->repairNumber(GateNum, enemy.at(i)->bonusFairy,enemy.at(i)->scorePoint,enemy.at(i)->getPosition());
							wallCount++;
						}
					}
				}
			}

			//壁にぶつかるか壊れてないゲートに入った時
			if (wallCount == 0)
			{
				layer->effect->fairyAscension(enemy.at(i)->getPosition(),enemy.at(i)->typeNum);
				((WatchLayer*)(this->getParent()))->effectPlayMusic(6);
			}


			deleteEnemy(i,false);
			return;
		}

		aura.at(i)->setPosition(enemy.at(i)->getPosition());

	}
}

void EnemyManager::deleteEnemy(int enemyNum,bool death)
{
	wallCount = 0;
	if (death)
	{
		((WatchLayer*)(this->getParent()))->effectPlayMusic(5);
		((WatchLayer*)(this->getParent()))->effect->fairyJunk(enemy.at(enemyNum)->getPosition(),enemy.at(enemyNum)->typeNum);
	}

		enemy.at(enemyNum)->removeFromParentAndCleanup(true);
		enemy.erase(enemyNum);
		aura.at(enemyNum)->removeFromParentAndCleanup(true);
		aura.erase(enemyNum);
}

//出現率計算
int EnemyManager::fairyAdvent()
{
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> EType(1, 100);
	int a = EType(mt);
	int advent;

	if (a <= 10)
	{
		advent = 1;
	}
	else if (a > 10 && a <= 30)
	{
		advent = 2;
	}
	else if(a > 31 && a <= 45)
	{
		advent = 3;
	}
	else
	{
		advent = 0;
	}

	return advent;
}