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

	void fairyDeath(Vec2 deathPos);  //妖精の死
	void shining(Vec2 shinPos);      //ぴかぴかする
	void numberShining(Vec2 numSPos);//中心からぴかぴかする
	void fairyAscension(Vec2 APos,int fairyType);  //妖精壁に当たり昇天
	void chargeEffect(Vec2 chPos);   //チャージ演出
	void fairyJunk(Vec2 JPos,int fairyType);       //妖精飛び散る
	void numWave(int num,int way);   //数字の波動
	void pointGet(Vec2 PointPos, int point,bool bonusCheck); //獲得したスコアがどのくらいか

	bool init();

private:

};
#endif