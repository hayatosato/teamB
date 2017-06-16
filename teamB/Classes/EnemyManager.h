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

	int   pos;                         //�d�������|�C���g
	int   createPos;                   //�󂯎���������|�C���g��ۑ�
	float ang;                         //���j�̊o��
	float tAng;                        //�d���̊p�x
	float fairyGateAng;                //�d���o���|�C���g�̊p�x

	float shotAng;                     //�Z�j�̊p�x
	float secondAng;                   //�b�j�̊p�x

	void fairyCreate(int fairyCreatePos);    //����
	
	void  update(float delta);

private:
	Vector<Sprite*> aura;                         //�d�����

	void  EnemyCreater(float dt);                 //�G����
	void  deleteEnemy(int enemyNum,bool death);   //�d���폜(�폜����d���̃i���o�[�Atrue�Ȃ玀��ŏ���)

};

#endif