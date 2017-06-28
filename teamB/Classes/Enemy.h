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
	int myCreatePos;           //���g���o���Q�[�g�̏ꏊ

	//����
	bool exitNeedle;        //�j����o����
	bool bonusFairy;        //�{�[�i�X���������Ă��邩�ǂ���

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

	//update
	void update(float dt);
private:

	Animation *animation;
	Animate *action;
	RepeatForever *anime;

	int bonusEffectCount; //�{�[�i�X���̃G�t�F�N�g�̔����p�x

	//�X�e�[�^�X
	float _speed;	//�ړ����x



};

#endif