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

USING_NS_CC;
using namespace std;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();

	bool masterHand;                    //�����true�ɂ��Ȃ�������b�j�͉��Ȃ�

	Title*         title;               //�^�C�g��
	TextNavi*      navi;
	EffectManager* effect;              //�G�t�F�N�g�}�l�[�W���[
	UIManager*     UI;                  //UI�}�l�[�W���[
	TimeLabel*     timeLabel;           //����

	float maxNumberHP;                  //�����̍ő�̗�
	float numberHP[WATCH_NUMBER];       //�����̗̑�
	float radius;                       //���a

	int   breakNum;                     //�󂷐����̐�
	int   nowBreakNum;                  //���݂̎�������ꂽ��
	int   breakNumCheck;                //�󂷐��������h�~
	int   actingBreak;                  //�󂷐�����I������Ƃ��Ɏg�p
	bool  breakCheck[WATCH_NUMBER];     //�󂷐������d�h�~

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

	void repairNumber(int num,bool bonus);    //�����̏C��&�N���A�������ǂ���
	void adventGateMotion(int GatePos);       //�G�o�����o&�G�𐶐����鏈�����Ă�
	void startCountDown();                    //�n�܂�
	void start();                             //�܂݂������A�b�j�������A�d�����N������

	void update(float delta);
private:

	Sprite* timeWaku;  //���Ԃ̘g
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