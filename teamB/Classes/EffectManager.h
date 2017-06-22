#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include <random>
#include "DeathFairy.h"
#include "Shine.h"
USING_NS_CC;
using namespace std;

class EffectManager : public Node
{
public:
	CREATE_FUNC(EffectManager);

	void fairyDeath(Vec2 deathPos);  //妖精の死
	void shining(Vec2 shinPos);      //ぴかぴかする
	void numberShining(Vec2 numSPos);//中心からぴかぴかする
	void fairyAscension(Vec2 APos);  //妖精壁に当たり昇天

	bool init();

private:

};
#endif