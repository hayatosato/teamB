#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	//ŽžŒv‚ÌˆÊ’u
	Vec2 watchPos = designResolutionSize * 0.5f;

<<<<<<< HEAD
	back = Sprite::create("backFactory.png");
	back->setPosition(designResolutionSize.width / 2, designResolutionSize.height *0.4f);
	this->addChild(back);
=======
	//”wŒi
	LayerColor* layerColor = LayerColor::create(Color4B::GREEN, designResolutionSize.width, designResolutionSize.height);
	this->addChild(layerColor);
>>>>>>> 4fd1ba1ef1549ef0a3e53f28073be19d237a49df

	//‚Â‚Ü‚Ý
	_knob = Knob::create();
<<<<<<< HEAD
	_knob->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.5f);
	this->addChild(_knob, 10);

	//ŽžŒv
	_watchSprite = Sprite::create("Watch.png");
	_watchSprite->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
=======
	_knob->setPosition(Vec2(watchPos.x + watchPos.x * 0.9f, watchPos.y));
	_knob->setScale(3.0f);
	this->addChild(_knob);

	//ŽžŒv
	_watchSprite = Sprite::create("Watch.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(3.0f);
>>>>>>> 4fd1ba1ef1549ef0a3e53f28073be19d237a49df
	this->addChild(_watchSprite);

	//’Zj
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	_shortHand->setScale(3.0f);
	this->addChild(_shortHand);

	//’·j
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	_longHand->setScale(3.0f);
	this->addChild(_longHand);

	//PlayerƒNƒ‰ƒX
	_player = Player::create();
	this->addChild(_player);

	//EnemyManagerƒNƒ‰ƒX
	_enemyManager = EnemyManager::create();
	this->addChild(_enemyManager);

	return true;
}