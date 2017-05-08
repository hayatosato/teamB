#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class EnemyManager : public Node 
{
public:
	//CREATE_FUNC(EnemyManager);
	static EnemyManager *create(int formPosNum);

	virtual bool init(int formPosNum);

	int createPos;
	
	//ìGê∂ê¨
	void EnemyCreater(float dt);

private:
};

#endif