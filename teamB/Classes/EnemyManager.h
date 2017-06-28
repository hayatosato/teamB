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

	bool masterFairy;                  //‚±‚ê‚ğtrue‚É‚µ‚È‚¢‚©‚¬‚è—d¸‚Í—N‚©‚È‚¢

	Vector<Enemy*> enemy;
	int multipleNum[12];               //“¯‚¶ŒÂŠ‚É—d¸‚ª—N‚©‚È‚¢‚æ‚¤‚É
	virtual bool init(int formPosNum);

	int   pos;                         //—d¸¶¬ƒ|ƒCƒ“ƒg
	int   createPos;                   //ó‚¯æ‚Á‚½¶¬ƒ|ƒCƒ“ƒg‚ğ•Û‘¶
	float ang;                         //’·j‚ÌŠoŒå
	float tAng;                        //—d¸‚ÌŠp“x
	float fairyGateAng;                //—d¸oŒ»ƒ|ƒCƒ“ƒg‚ÌŠp“x

	float shotAng;                     //’Zj‚ÌŠp“x
	float secondAng;                   //•bj‚ÌŠp“x

	void fairyCreate(int fairyCreatePos);    //¶¬
	
	void  update(float delta);

private:
	Vector<Sprite*> aura;                         //—d¸ŒãŒõ

	int wallCount;                                //•ÇÕ“Ë”»’è‚Ég—p

	void  EnemyCreater(float dt);                 //“G¶¬
	void  deleteEnemy(int enemyNum,bool death);   //—d¸íœ(íœ‚·‚é—d¸‚Ìƒiƒ“ƒo[Atrue‚È‚ç€‚ñ‚ÅÁ–Å)

};

#endif