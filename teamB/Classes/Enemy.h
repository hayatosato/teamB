#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"	
USING_NS_CC;

class Enemy : public Sprite
{
public:
	CREATE_FUNC(Enemy);
	virtual bool init();

	int startCount;            //移動開始までのカウント

	//動作
	bool exitNeedle;        //針から出たか
	bool bonusFairy;        //ボーナスがかかっているかどうか

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


	//ステータス
	//float shotLength;   //短針の長さ
	float _speed;	//移動速度

};

#endif