#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class EnemyManager : public Node 
{
public:
	CREATE_FUNC(EnemyManager);
	virtual bool init();
	
	//ìGê∂ê¨
	void EnemyCreater(float dt);

private:
};

#endif