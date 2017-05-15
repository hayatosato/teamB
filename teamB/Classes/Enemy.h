#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"	
USING_NS_CC;

class Enemy : public Sprite
{
public:
	CREATE_FUNC(Enemy);
	virtual bool init();

	//update
	void update(float dt);
	bool moveMode;          //������

	//����
	void Move(float deltaTime);
	void Hit();
private:

	//����
	bool HoldCheck(Vec2 pos, Rect shortRect, Rect longRect);
	bool JastHandCheck(float shortRotate, float longRotate);

	//�X�e�[�^�X
	float _speed;	//�ړ����x
};

#endif