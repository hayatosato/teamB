#ifndef _WATCH_LAYER_H_
#define _WATCH_LAYER_H_

#include "cocos2d.h"
#include "Knob.h"
#include "ShortHand.h"
#include "LongHand.h"
#include "Player.h"
#include "EnemyManager.h"

USING_NS_CC;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();
<<<<<<< HEAD

	Sprite* back;   //‰¼”wŒi
	//j
	ShortHand* _shortHand;
	LongHand* _longHand;
=======
>>>>>>> 4fd1ba1ef1549ef0a3e53f28073be19d237a49df

	//‚Â‚Ü‚İ
	Knob* _knob;

	//j
	ShortHand* _shortHand;
	LongHand* _longHand;

	//PlayerƒNƒ‰ƒX
	Player* _player;
private:
	//Œv@”wŒi
	Sprite* _watchSprite;

	

	//EnemyManagerƒNƒ‰ƒX
	EnemyManager* _enemyManager;
};

#endif