#ifndef _WATCH_LAYER_H_
#define _WATCH_LAYER_H_

#include "cocos2d.h"
#include <vector>
#include <math.h>
#include "Knob.h"
#include "ShortHand.h"
#include "LongHand.h"
#include "SecondHand.h"
#include "Player.h"
#include "EnemyManager.h"

USING_NS_CC;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();

	int circle;                         //�z�u����G�����n�_�̐�
	float radius;                       //���a

	vector<Sprite*> fairyGate;          //�G�����n�_

	Knob* _knob;                        //�܂�

	//�j
	ShortHand* _shortHand;
	LongHand* _longHand;
	SecondHand* _secondHand;

	//���v�@�w�i
	Sprite* _watchSprite;
	//Player�N���X
	Player* _player;

	void update(float delta);
private:

	//EnemyManager�N���X
	EnemyManager* _enemyManager;
};

#endif