#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"	
USING_NS_CC;

class Enemy : public Sprite
{
public:
	CREATE_FUNC(Enemy);
	virtual bool init();

	//update
	void update(float dt);
	bool moveMode;          //動くか

	//動作
	void Move(float deltaTime);
	void Hit();
private:

	//判定
	bool HoldCheck(Vec2 pos, Rect shortRect, Rect longRect);
	bool JastHandCheck(float shortRotate, float longRotate);

	//ステータス
	float _speed;	//移動速度
};

#endif