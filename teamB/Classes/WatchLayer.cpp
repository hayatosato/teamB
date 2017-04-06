#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	//時計の位置
	Vec2 watchPos = designResolutionSize * 0.5f;

	back = Sprite::create("backFactory.png");
	back->setPosition(designResolutionSize.width / 2, designResolutionSize.height *0.4f);
	this->addChild(back);

	//背景
	LayerColor* layerColor = LayerColor::create(Color4B::GREEN, designResolutionSize.width, designResolutionSize.height);
	this->addChild(layerColor);


	//つまみ
	_knob = Knob::create();
	_knob->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.5f);
	this->addChild(_knob, 10);

	//時計
	_watchSprite = Sprite::create("Watch.png");
	_watchSprite->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	_knob->setPosition(Vec2(watchPos.x + watchPos.x * 0.9f, watchPos.y));
	_knob->setScale(3.0f);
	this->addChild(_knob);

	//時計
	_watchSprite = Sprite::create("Watch.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(3.0f);
	this->addChild(_watchSprite);

	//短針
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	_shortHand->setScale(3.0f);
	this->addChild(_shortHand);

	//長針
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	_longHand->setScale(3.0f);
	this->addChild(_longHand);

	//Playerクラス
	_player = Player::create();
	this->addChild(_player);

	//EnemyManagerクラス
	_enemyManager = EnemyManager::create();
	this->addChild(_enemyManager);

	return true;
}