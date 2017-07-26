#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include <random>
#include "DeathFairy.h"
#include "Shine.h"
#include "Junk.h"
#include "SurgeNum.h"
#include "PointLabel.h"
#include "KNobEffect.h"

USING_NS_CC;
using namespace std;

class EffectManager : public Node
{
public:
	CREATE_FUNC(EffectManager);

	void fairyDeath(Vec2 deathPos);  //�d���̎�
	void shining(Vec2 shinPos);      //�҂��҂�����
	void numberShining(Vec2 numSPos);//���S����҂��҂�����
	void fairyAscension(Vec2 APos,int fairyType);  //�d���ǂɓ����菸�V
	void chargeEffect(Vec2 chPos);   //�`���[�W���o
	void fairyJunk(Vec2 JPos,int fairyType);       //�d����юU��
	void numWave(int num,int way);   //�����̔g��
	void pointGet(Vec2 PointPos, int point,bool bonusCheck); //�l�������X�R�A���ǂ̂��炢��
	void subPointGet(Vec2 subPointPos, int subPoint, bool subBonusCheck); //�����̃X�R�A�l��
	void kNobTurn(Vec2 kNobPos); //�܂݃A�s�[��
	void yajiErase();           //�`���[�g���A���̖�󂯂�

	bool init();

private:

};
#endif