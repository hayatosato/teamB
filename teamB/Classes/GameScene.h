#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "CenterObject.h"
#include "RedClock.h"
#include "BlueClock.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	virtual bool init();
	// タッチイベント処理
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);

	CREATE_FUNC(GameScene);

private:
	//Object
	CenterObject *_centerObj;
	RedClock *_redClock;
	BlueClock *_blueClock;

};

#endif