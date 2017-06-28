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

USING_NS_CC;
using namespace std;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();

	bool masterHand;                    //これをtrueにしないかぎり秒針は回らない

	EffectManager* effect;              //エフェクトマネージャー
	UIManager*     UI;                  //UIマネージャー
	TimeLabel*     timeLabel;           //時間

	float maxNumberHP;                  //数字の最大体力
	float numberHP[WATCH_NUMBER];       //数字の体力
	float radius;                       //半径

	int   breakNum;                     //壊す数字の数
	int   nowBreakNum;                  //現在の治った壊れた数
	int   breakNumCheck;                //壊す数字増加防止
	int   actingBreak;                  //壊す数字を選択するときに使用
	bool  breakCheck[WATCH_NUMBER];     //壊す数字多重防止

	vector<FairyGate*> fairyGate;          //敵発生地点
	vector<Sprite*> numSpr;             //数字の画像

	Knob*       _knob;                  //つまみ
	ShortHand*  _shortHand;             //短針
	LongHand*   _longHand;              //長針
	SecondHand* _secondHand;            //秒針

	//時計　背景
	Sprite* _watchSprite;
	Sprite* dirtWatch;       //時計の汚れなど
	Sprite* glassShine;      //ガラスの反射
	Player* _player;         //Playerクラス

	void repairNumber(int num,bool bonus);    //数字の修復&クリアしたかどうか
	void adventGateMotion(int GatePos);       //敵出現演出&敵を生成する処理を呼ぶ
	void start();                             //つまみが動き、秒針が動き、妖精が湧きだす

	void update(float delta);
private:

	Sprite* backDesk;  //背景
	Sprite* timeWaku;  //時間の枠
	//皮
	Sprite* backOne;
	Sprite* backTwo;

	float repairScore;        //数字が回復する値
	float repairBonusScore;   //ボーナス時の数字が回復する値

	//EnemyManagerクラス
	EnemyManager* _enemyManager;
	int   circleNum;                         //配置する敵発生地点の数

	void ramdomBreak();    //壊れた数字の配置
};

#endif