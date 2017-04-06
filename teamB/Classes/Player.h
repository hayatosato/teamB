#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	// タッチイベント処理
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	//動いているか
	bool _isMove;
private:
	//フラグ
	bool _knobFlg;
};

#endif