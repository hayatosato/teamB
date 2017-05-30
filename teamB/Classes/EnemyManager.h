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

	int createPos;                     //ó‚¯æ‚Á‚½¶¬ƒ|ƒCƒ“ƒg‚ğ•Û‘¶
	float ang;                         //’·j‚ÌŠoŒå
	float tAng;                        //“G‚ÌŠp“x

	float shotAng;                     //’Zj‚ÌŠp“x
	float secondAng;                   //•bj‚ÌŠp“x
	
	//“G¶¬
	void EnemyCreater(float dt);
	void update(float delta);

private:

};

#endif