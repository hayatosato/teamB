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

	void fairyDeath(Vec2 deathPos);  //ódê∏ÇÃéÄ
	void shining(Vec2 shinPos);      //Ç“Ç©Ç“Ç©Ç∑ÇÈ
	void numberShining(Vec2 numSPos);//íÜêSÇ©ÇÁÇ“Ç©Ç“Ç©Ç∑ÇÈ

	bool init();

private:

};
#endif