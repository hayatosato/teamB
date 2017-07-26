#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"	
USING_NS_CC;

class Enemy : public Sprite
{
public:
	//CREATE_FUNC(Enemy);
	static Enemy *create(int type);
	virtual bool init(int type);

	int typeNum;               //妖精の種類
	int startCount;            //移動開始までのカウント
	int myCreatePos;           //自身が出たゲートの場所
	int scorePoint;            //自身の持っているスコアポイント

	//動作
	bool exitNeedle;        //針から出たか
	bool bonusFairy;        //ボーナスがかかっているかどうか

	bool downMode;          //特殊妖精か判断

	enum fairyMode
	{
		WAIT,
		GO,
		BACK,
		SAVEONE,
		SAVETWO
	};
	enum fairyMode fairyModes;

	void resetCount();              //startCountをリセット
	void Move(float deltaTime);     //動き

	//update
	void update(float dt);
private:

	Animation *animation;
	Animate *action;
	RepeatForever *anime;

	int bonusEffectCount; //ボーナス時のエフェクトの発生頻度

	//ステータス
	float _speed;	//移動速度



};

#endif