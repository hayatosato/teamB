#ifndef _WATCH_LAYER_H_
#define _WATCH_LAYER_H_
#define WATCH_NUMBER 12

#include "cocos2d.h"
#include <vector>
#include <math.h>
#include <string>
#include "Knob.h"
#include "ShortHand.h"
#include "LongHand.h"
#include "SecondHand.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "FairyGate.h"
#include "Calculation.h"
#include "UIManager.h"
#include "TimeLabel.h"
#include "Title.h"
#include "TextNavi.h"
#include "Clear.h"
#include "ClearText.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();

	bool masterHand;                    //�����true�ɂ��Ȃ�������b�j�͉��Ȃ�

	Title*         title;               //�^�C�g��
	TextNavi*      navi;                //taptostart
	Sprite*        blackBack;           //���̊D�F
	EffectManager* effect;              //�G�t�F�N�g�}�l�[�W���[
	UIManager*     UI;                  //UI�}�l�[�W���[
	TimeLabel*     timeLabel;           //����
	UserDefault*   timeScore;           //���ԕۑ��p
	Clear*         clear;               //�N���A�摜
	bool highScoreCheck;                //�n�C�X�R�A���X�V�������ǂ���

	float maxNumberHP;                  //�����̍ő�̗�
	float numberHP[WATCH_NUMBER];       //�����̗̑�
	float radius;                       //���a

	int   breakNum;                     //�󂷐����̐�
	int   nowBreakNum;                  //���݂̎�������ꂽ��
	int   breakNumCheck;                //�󂷐��������h�~
	int   actingBreak;                  //�󂷐�����I������Ƃ��Ɏg�p
	bool  breakCheck[WATCH_NUMBER];     //�󂷐������d�h�~

	int   maxKnobCount;                 //�ő�܂݋����J�E���g
	int   knobCount;                    //�܂݋����J�E���g
	bool  knobSwitch;                   //true�ŉ��o

	vector<FairyGate*> fairyGate;       //�G�����n�_
	vector<Sprite*> numSpr;             //�����̉摜

	Knob*       _knob;                  //�܂�
	ShortHand*  _shortHand;             //�Z�j
	LongHand*   _longHand;              //���j
	SecondHand* _secondHand;            //�b�j

	//���v�@�w�i
	Sprite* _watchSprite;
	Sprite* dirtWatch;       //���v�̉���Ȃ�
	Sprite* glassShine;      //�K���X�̔���
	Player* _player;         //Player�N���X
	ClearText* clearText;

	void repairNumber(int num,bool bonus,int fairyScore,Vec2 fairyPos);    //�����̏C��&�N���A�������ǂ���&�X�R�A�擾
	void adventGateMotion(int GatePos);       //�G�o�����o&�G�𐶐����鏈�����Ă�
	void startCountDown();                    //�n�܂�
	void start();                             //�܂݂������A�b�j�������A�d�����N�������A�J�E���g�A�b�v���n�߂�
	void end();                               //�܂݂��~�߁A�b�j���~�߁A�d�����~�߁A�J�E���g�A�b�v���~������
	void stopMusic();                         //�����~�߂�
	void effectPlayMusic(int musicNum);       //�ԍ��ɂ�����SE�𗬂�
	void plusScore(int upScore);              //�X�R�A�𑫂�
	void createModoru();

	void update(float delta);
private:

	Vec2 UIPos;        //UI��_
	Vec2 timePos;      //���Ԋ�_

	Sprite* timeWaku;  //���Ԃ̘g
	Sprite* timeBoard; //���Ԃ̔�
	Sprite* countThree;//�J�E���g�_�E���̉摜3
	Sprite* countTwo;  //�J�E���g�_�E���̉摜2
	Sprite* countOne;  //�J�E���g�_�E���̉摜1

	//�J�E���g�_�E�����o�Ɏg�p
	ScaleTo* scaleTo;
	CallFunc* dThree;
	CallFunc* dTwo;
	CallFunc* dOne;
	Sequence* seqThree;
	Sequence* seqTwo;
	Sequence* seqOne;
	void cTwo(float delta);  //2�̓���
	void cOne(float delta);  //3�̓���

	MoveTo* timeMove;     //�J�E���g�̓���
	MoveTo* UIMove;       //���Q�[�W�̓���

	//��
	Sprite* backOne;
	Sprite* backTwo;

	float repairScore;        //�������񕜂���l
	float repairBonusScore;   //�{�[�i�X���̐������񕜂���l

	//EnemyManager�N���X
	EnemyManager* _enemyManager;
	int   circleNum;                         //�z�u����G�����n�_�̐�

	void showingNeedle();  //�����Ȃ������j��������
	void ramdomBreak();    //��ꂽ�����̔z�u
};
#endif