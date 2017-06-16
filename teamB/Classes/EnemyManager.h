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

	int   pos;                         //dΈΆ¬|Cg
	int   createPos;                   //σ―ζΑ½Ά¬|CgπΫΆ
	float ang;                         //·jΜoε
	float tAng;                        //dΈΜpx
	float fairyGateAng;                //dΈo»|CgΜpx

	float shotAng;                     //ZjΜpx
	float secondAng;                   //bjΜpx

	void fairyCreate(int fairyCreatePos);    //Ά¬
	
	void  update(float delta);

private:
	Vector<Sprite*> aura;                         //dΈγυ

	void  EnemyCreater(float dt);                 //GΆ¬
	void  deleteEnemy(int enemyNum,bool death);   //dΈν(ν·ιdΈΜio[AtrueΘηρΕΑΕ)

};

#endif