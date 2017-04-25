#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	//時計の位置
	Vec2 watchPos = designResolutionSize * 0.5f;

	//背景
	//LayerColor* layerColor = LayerColor::create(Color4B::GREEN, designResolutionSize.width, designResolutionSize.height);
	//this->addChild(layerColor);

	//時計
	_watchSprite = Sprite::create("GameScene/clockNum.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(0.6f);
	this->addChild(_watchSprite,1);

	//つまみ
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize.width * 0.96f, watchPos.y));
	_knob->setScale(0.5f);
	this->addChild(_knob,0);

	//短針
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	//_shortHand->setScale(3.0f);
	this->addChild(_shortHand,2);

	//長針
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	//_longHand->setScale(3.0f);
	this->addChild(_longHand,3);

	//Playerクラス
	_player = Player::create();
	this->addChild(_player);

	//EnemyManagerクラス
	_enemyManager = EnemyManager::create();
	this->addChild(_enemyManager,4);

	return true;
}