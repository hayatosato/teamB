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
	int  numberHP[WATCH_NUMBER];         //数字の体力
	float radius;                       //半径

	int  breakNum;                       //壊す数字の数
	int  breakNumCheck;                  //壊す数字増加防止
	int  actingBreak;                    //壊す数字を選択するときに使用
	bool breakCheck[WATCH_NUMBER];       //壊す数字多重防止

	vector<Sprite*> fairyGate;          //敵発生地点
	vector<Sprite*> numSpr;             //数字の画像

	Knob* _knob;                        //つまみ

	//針
	ShortHand*  _shortHand;
	LongHand*   _longHand;
	SecondHand* _secondHand;

	//時計　背景
	Sprite* _watchSprite;
	Sprite* dirtWatch;       //時計の汚れなど
	Sprite* glassShine;      //ガラスの反射
	//Playerクラス
	Player* _player;

	void repairNumber(int num);    //数字の修復&クリアしたかどうか
	void update(float delta);
private:

	//EnemyManagerクラス
	EnemyManager* _enemyManager;
	int   circleNum;                         //配置する敵発生地点の数

	void ramdomBreak();    //壊れた数字の配置
};

#endif