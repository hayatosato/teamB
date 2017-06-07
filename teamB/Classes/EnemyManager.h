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

	Vector<Enemy*> enemy;
	virtual bool init(int formPosNum);

	int pos;                           //—d¸¶¬ƒ|ƒCƒ“ƒg
	int createPos;                     //ó‚¯æ‚Á‚½¶¬ƒ|ƒCƒ“ƒg‚ğ•Û‘¶
	float ang;                         //’·j‚ÌŠoŒå
	float tAng;                        //—d¸‚ÌŠp“x
	float fairyGateAng;                //—d¸oŒ»ƒ|ƒCƒ“ƒg‚ÌŠp“x

	float shotAng;                     //’Zj‚ÌŠp“x
	float secondAng;                   //•bj‚ÌŠp“x
	
	void EnemyCreater(float dt);       //“G¶¬
	void deleteEnemy(int enemyNum);    //—d¸íœ
	void update(float delta);

private:

};

#endif