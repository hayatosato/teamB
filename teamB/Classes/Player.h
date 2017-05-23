#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	// �^�b�`�C�x���g����
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	bool _isMove;     //�����Ă��邩
	bool parallel;  //���j�ƒZ�j�����s��

	float longDir;         //���j�̊p�x�擾
	float shortDir;        //�Z�j�̊p�x�擾
	float longMoveDir;     //���j�̓����p�x�v�Z�p
	float shortMoveDir;    //�Z�j�̓����p�x�v�Z�p
	float longDirF;        //���j�̊p�x�ω�

	void update(float delta);
private:
	int crackCount;        //�K���X���^�b�`�����񐔂��J�E���g
	bool crush;            //�K���X������Ă��邩�̔��f

	//�t���O
	bool _knobFlg;
	float downMove;        //�j�̃X�s�[�h�������Ă����X�s�[�h
	float maxMoveSpeed;    //�j�̍ő�X�s�[�h

	void downSpeed();
};

#endif