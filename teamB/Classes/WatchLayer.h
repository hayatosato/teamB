#ifndef _WATCH_LAYER_H_
#define _WATCH_LAYER_H_

#include "cocos2d.h"
#include "Player.h"
#include "Knob.h"
#include "ShortHand.h"
#include "LongHand.h"

USING_NS_CC;

class WatchLayer : public Layer
{
public:
	CREATE_FUNC(WatchLayer);
	virtual bool init();
	//j
	ShortHand* _shortHand;
	LongHand* _longHand;

	//‚Â‚Ü‚İ
	Knob* _knob;

private:
	//˜rŒv@”wŒi
	Sprite* _watchSprite;

	//PlayerƒNƒ‰ƒX
	Player* _player;
};

#endif