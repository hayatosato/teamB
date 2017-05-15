#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
#include "Calculation.h"
#include <vector>

USING_NS_CC;
using namespace std;

class EnemyManager : public Node 
{
public:
	static EnemyManager *create(int formPosNum);

	vector<Enemy*> enemy;
	virtual bool init(int formPosNum);

	int createPos;                     //受け取った生成ポイントを保存
	float ang;                         //針の覚悟
	float tAng;                        //敵の角度
	
	//敵生成
	void EnemyCreater(float dt);
	void update(float delta);

private:

};

#endif