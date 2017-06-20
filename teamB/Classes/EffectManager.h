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

	void fairyDeath(Vec2 deathPos);  //�d���̎�
	void shining(Vec2 shinPos);      //�҂��҂�����
	void numberShining(Vec2 numSPos);//���S����҂��҂�����

	bool init();

private:

};
#endif