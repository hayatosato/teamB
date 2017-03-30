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
	//�j
	ShortHand* _shortHand;
	LongHand* _longHand;

	//�܂�
	Knob* _knob;

private:
	//�r���v�@�w�i
	Sprite* _watchSprite;

	//Player�N���X
	Player* _player;
};

#endif