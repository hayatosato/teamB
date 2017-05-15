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

	int createPos;                     //�󂯎���������|�C���g��ۑ�
	float ang;                         //�j�̊o��
	float tAng;                        //�G�̊p�x
	
	//�G����
	void EnemyCreater(float dt);
	void update(float delta);

private:

};

#endif