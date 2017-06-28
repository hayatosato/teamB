#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

	bool masterTap;           //これをtrueにしない限りタップ関係は動かない

	// タッチイベント処理
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	Vec2 delta;

	bool _isMove;     //動いているか
	bool parallel;  //長針と短針が平行か

	float longDir;         //長針の角度取得
	float shortDir;        //短針の角度取得
	float longMoveDir;     //長針の動く角度計算用
	float shortMoveDir;    //短針の動く角度計算用
	float longDirF;        //長針の角度変化

	void update(float delta);
private:

	//フラグ
	bool _knobFlg;
	float downMove;        //針のスピードが落ちていくスピード
	float maxMoveSpeed;    //針の最大スピード

	void downSpeed();
};

#endif