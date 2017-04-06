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

	//つまみ
	Knob* _knob;

	//針
	ShortHand* _shortHand;
	LongHand* _longHand;

	//Playerクラス
	Player* _player;
private:
	//時計　背景
	Sprite* _watchSprite;

	//EnemyManagerクラス
	EnemyManager* _enemyManager;
};

#endif