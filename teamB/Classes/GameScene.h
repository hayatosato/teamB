#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "WatchLayer.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();


private:
	//Layer
	WatchLayer* _watchLayer;
};
#endif