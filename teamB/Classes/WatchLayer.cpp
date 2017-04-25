#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	//���v�̈ʒu
	Vec2 watchPos = designResolutionSize * 0.5f;

	//�w�i
	//LayerColor* layerColor = LayerColor::create(Color4B::GREEN, designResolutionSize.width, designResolutionSize.height);
	//this->addChild(layerColor);

	//���v
	_watchSprite = Sprite::create("GameScene/clockNum.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(0.6f);
	this->addChild(_watchSprite,1);

	//�܂�
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize.width * 0.96f, watchPos.y));
	_knob->setScale(0.5f);
	this->addChild(_knob,0);

	//�Z�j
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	//_shortHand->setScale(3.0f);
	this->addChild(_shortHand,2);

	//���j
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	//_longHand->setScale(3.0f);
	this->addChild(_longHand,3);

	//Player�N���X
	_player = Player::create();
	this->addChild(_player);

	//EnemyManager�N���X
	_enemyManager = EnemyManager::create();
	this->addChild(_enemyManager,4);

	return true;
}