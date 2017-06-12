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

USING_NS_CC;
using namespace std;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();
	int  numberHP[WATCH_NUMBER];         //�����̗̑�
	float radius;                       //���a

	int  breakNum;                       //�󂷐����̐�
	int  breakNumCheck;                  //�󂷐��������h�~
	int  actingBreak;                    //�󂷐�����I������Ƃ��Ɏg�p
	bool breakCheck[WATCH_NUMBER];       //�󂷐������d�h�~

	vector<Sprite*> fairyGate;          //�G�����n�_
	vector<Sprite*> numSpr;             //�����̉摜

	Knob* _knob;                        //�܂�

	//�j
	ShortHand*  _shortHand;
	LongHand*   _longHand;
	SecondHand* _secondHand;

	//���v�@�w�i
	Sprite* _watchSprite;
	Sprite* dirtWatch;       //���v�̉���Ȃ�
	Sprite* glassShine;      //�K���X�̔���
	//Player�N���X
	Player* _player;

	void repairNumber(int num);    //�����̏C��&�N���A�������ǂ���
	void update(float delta);
private:

	//EnemyManager�N���X
	EnemyManager* _enemyManager;
	int   circleNum;                         //�z�u����G�����n�_�̐�

	void ramdomBreak();    //��ꂽ�����̔z�u
};

#endif