#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include <random>
#include "DeathFairy.h"
#include "Shine.h"
#include "Junk.h"
#include "SurgeNum.h"
#include "PointLabel.h"

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

	bool init();

private:

};
#endif