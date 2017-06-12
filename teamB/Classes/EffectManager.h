#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include "DeathFairy.h"
USING_NS_CC;

class EffectManager : public Node
{
public:
	CREATE_FUNC(EffectManager);

	void fairyDeath(Vec2 deathPos);

	bool init();

private:

};
#endif