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

	bool masterFairy;                  //これをtrueにしないかぎり妖精は湧かない

	Vector<Enemy*> enemy;
	int multipleNum[12];               //同じ個所に妖精が湧かないように
	virtual bool init(int formPosNum);

	int   pos;                         //妖精生成ポイント
	int   createPos;                   //受け取った生成ポイントを保存
	float ang;                         //長針の覚悟
	float tAng;                        //妖精の角度
	float fairyGateAng;                //妖精出現ポイントの角度

	float shotAng;                     //短針の角度
	float secondAng;                   //秒針の角度

	void fairyCreate(int fairyCreatePos);    //生成
	
	void  update(float delta);

private:
	Vector<Sprite*> aura;                         //妖精後光

	int wallCount;                                //壁衝突判定に使用

	void  EnemyCreater(float dt);                 //敵生成
	void  deleteEnemy(int enemyNum,bool death);   //妖精削除(削除する妖精のナンバー、trueなら死んで消滅)

};

#endif