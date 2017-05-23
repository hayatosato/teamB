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

	int circle;                         //配置する敵発生地点の数
	float radius;                       //半径

	vector<Sprite*> fairyGate;          //敵発生地点

	Knob* _knob;                        //つまみ

	//針
	ShortHand* _shortHand;
	LongHand* _longHand;
	SecondHand* _secondHand;

	//時計　背景
	Sprite* _watchSprite;
	//Playerクラス
	Player* _player;

	void update(float delta);
private:

	//EnemyManagerクラス
	EnemyManager* _enemyManager;
};

#endif