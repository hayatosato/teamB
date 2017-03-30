#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	Vec2 watchPos = designResolutionSize * 0.5f;

	//コンビニに行きました。

	//Knob
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize * 0.5f));
	this->addChild(_knob, 10);

	//時計
	_watchSprite = Sprite::create("Watch.png");
	_watchSprite->setPosition(watchPos);
	this->addChild(_watchSprite);

	//ShortHand
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	this->setScaleX(1.5);
	this->setScaleY(1.3);
	this->addChild(_shortHand);

	//LongHand
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	this->setScale(1.5);
	this->addChild(_longHand);

	//Playerクラス
	_player = Player::create();
	this->addChild(_player);

	return true;
}