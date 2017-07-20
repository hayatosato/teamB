#ifndef __CLEAR_TEXT_H__
#define __CLEAR_TEXT_H__

#include "cocos2d.h"
USING_NS_CC;

class ClearText : public Node
{
public:
	static ClearText *create(int HScore,int score,int nowM,int nowS,bool highScoreC);

	bool init(int HScore, int score, int nowM, int nowS, bool highScoreC);

	Label* nowScore;           //���݂̃X�R�A���x��
	Label* bonusChar;          //�{�[�i�X����
	Label* timeBonus;          //�^�C���\�����x��
	Label* highScore;          //�n�C�X�R�A���x��

	void skip();               //�X�R�A���Z�X�L�b�v

	void update(float delta);
	
private:
	int scorePoint;            //���݂̃X�R�A���擾
	int bonusPoint;            //�{�[�i�X�l���擾
	int highScorePoint;        //�n�C�X�R�A�l���擾

	bool sCheck;               //�n�C�X�R�A���X�V�������ǂ���
	bool bonusGate;            //true�ɂ���ƃ{�[�i�X���X�R�A�ɗ�������

	void timeBonusDisplay();
	void highScoreDisplay(float delta);


};
#endif