#ifndef _WATCH_LAYER_H_
#define _WATCH_LAYER_H_

#include "cocos2d.h"
#include "Knob.h"
#include "ShortHand.h"
#include "LongHand.h"
#include "Player.h"
#include "EnemyManager.h"

USING_NS_CC;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();

	Sprite* back;   //���w�i
	//�j
	ShortHand* _shortHand;
	LongHand* _longHand;


	//�܂�
	Knob* _knob;

	//Player�N���X
	Player* _player;
private:
	//���v�@�w�i
	Sprite* _watchSprite;

	

	//EnemyManager�N���X
	EnemyManager* _enemyManager;
};

#endif