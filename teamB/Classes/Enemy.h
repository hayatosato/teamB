#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"	
USING_NS_CC;

class Enemy : public Sprite
{
public:
	CREATE_FUNC(Enemy);
	virtual bool init();

	int startCount;            //�ړ��J�n�܂ł̃J�E���g

	//����
	bool moveMode;          //������
	enum fairyMode
	{
		WAIT,
		GO,
		BACK,
		SAVEONE,
		SAVETWO
	};
	enum fairyMode fairyModes;

	void resetCount();              //startCount�����Z�b�g
	void Move(float deltaTime);     //����
	void Hit();

	//update
	void update(float dt);
private:

	//����
	bool HoldCheck(Vec2 pos, Rect shortRect, Rect longRect);
	bool JastHandCheck(float shortRotate, float longRotate);

	//�X�e�[�^�X
	//float shotLength;   //�Z�j�̒���
	float _speed;	//�ړ����x

};

#endif