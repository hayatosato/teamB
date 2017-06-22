#include "EnemyManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

//�G�����Ԋu 3.0f
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

	createPos = formPosNum;
	wallCount = 0;
	//��莞�Ԃ��ƂɓG�𐶐�
	this->schedule(schedule_selector(EnemyManager::EnemyCreater), EnemyPopInterval);

	this->scheduleUpdate();

	return true;
}

//�G����
void EnemyManager::EnemyCreater(float dt)
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> posNum(0,createPos);
	//�G����
	pos = posNum(mt);
	if (((WatchLayer*)(this->getParent()))->breakCheck[pos] == true &&
		enemy.size() < 50)
	{
		//�z��̂���C��
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
	//�G����
	enemy.pushBack(Enemy::create());
	enemy.at(enemy.size() - 1)->setPosition(((WatchLayer*)(this->getParent()))->fairyGate.at(fairyCreatePos)->getPosition());
	this->addChild(enemy.at(enemy.size() - 1), 1);
	//�d���������
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
		float tAngPlus = tAng + 5.0f;
		float tAngMinus = tAng - 5.0f;
		if (tAngMinus <= 0)
		{
			tAngMinus += 360.0f;
		}
		//���j�Ɨd���������p�x��������
		if (ang < tAngPlus &&
			ang > tAngMinus &&
			enemy.at(i)->fairyModes == enemy.at(i)->WAIT
			)
		{
			enemy.at(i)->startCount--;
		}
		else
		{
			//12���̊p�x����
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

		//���j�ƕb�j�̊p�x�������ɂȂ������ǂ���
		if (ang < secondAng + 3.0f &&
			ang > secondAng - 3.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->GO || enemy.at(i)->fairyModes == enemy.at(i)->BACK)
			{
				deleteEnemy(i,true);
				return;
			}
		}

		//�Z�j�ƕb�j�̊p�x�������ɂȂ������ǂ���
		if (shotAng < secondAng + 3.0f &&
			shotAng > secondAng - 3.0f)
		{
			if (enemy.at(i)->fairyModes == enemy.at(i)->SAVEONE || enemy.at(i)->fairyModes == enemy.at(i)->SAVETWO)
			{
				deleteEnemy(i,true);
				return;
			}
		}

		//�d�����j�̍S������O�ꂽ��Q�[�g�Ƃ̊p�x�������ߋ߂������珈�������Ō�ɗd�����폜����
		if (enemy.at(i)->exitNeedle == false)
		{
			for (int a = 0; a < layer->fairyGate.size(); a++)
			{
				//�Q�[�g�̊p�x�擾
				fairyGateAng = Calculation::angle(designResolutionSize*0.5, layer->fairyGate.at(a)->getPosition());
				if (fairyGateAng < 0.0f)
				{
					fairyGateAng += 360.0f;
				}
				float fairyGateAngPlus = fairyGateAng + 5.0f;
				float fairyGateAngMinus = fairyGateAng - 5.0f;
				if (fairyGateAngMinus <= 0)
				{
					fairyGateAngMinus += 360.0f;
				}
				int GateNum = a;
				GateNum--;
				if (GateNum < 0) GateNum = 11;

				//�Q�[�g�̊p�x�Ɨd���̊p�x�������������Ƃ��Q�[�g�̏�Ԃ�\��
				if (tAng < fairyGateAngPlus &&
					tAng > fairyGateAngMinus)
				{
					if (layer->breakCheck[GateNum] == false)
					{
						layer->effect->shining(layer->fairyGate.at(a)->getPosition());
						layer->repairNumber(GateNum,enemy.at(i)->bonusFairy);
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
							layer->repairNumber(GateNum, enemy.at(i)->bonusFairy);
							wallCount++;
						}
					}
				}
			}

			//�ǂɂԂ��邩���ĂȂ��Q�[�g�ɓ�������
			if (wallCount == 0)
			{
				layer->effect->fairyAscension(enemy.at(i)->getPosition());
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
		((WatchLayer*)(this->getParent()))->effect->fairyDeath(enemy.at(enemyNum)->getPosition());
	}

		enemy.at(enemyNum)->removeFromParentAndCleanup(true);
		enemy.erase(enemyNum);
		aura.at(enemyNum)->removeFromParentAndCleanup(true);
		aura.erase(enemyNum);
}