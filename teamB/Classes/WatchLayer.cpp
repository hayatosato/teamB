#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	circle = 12;
	breakNumCheck = 0;
	breakNum = 3;

	for (int t = 0; t < 12; t++)
	{
		breakCheck[t] = true;
	}
	//時計の位置
	Vec2 watchPos = designResolutionSize * 0.5f;

	//時計
	_watchSprite = Sprite::create("GameScene/clockOne.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(0.6f);
	this->addChild(_watchSprite,1);

	radius = (_watchSprite->getContentSize().width*0.5f)*0.6f;

	//妖精発生地点設定&ゲート画像配置
	for (int i = 0; i < circle; i++)
	{
		fairyGate.push_back(Sprite::create("GameScene/EnemySprite.png"));
		fairyGate.at(i)->setPosition(Vec2(designResolutionSize.width*0.5f + radius*cos(M_PI / 180 * (90 - 360 * i / circle)),
			                              designResolutionSize.height*0.5f + radius*sin(M_PI / 180 * (90 - 360 * i / circle))));
		fairyGate.at(i)->setScale(0.3f);
		this->addChild(fairyGate.at(i),5);
	}
	//fairyGate.at(2)->setColor(Color3B::GREEN);
	//数字を表示
	for (int j = 0; j < 12; j++)
	{
		String* noNum = String::createWithFormat("GameScene/clockTwo-%d.png", j + 1);
		numSpr.push_back(Sprite::create(noNum->getCString()));
		numSpr.at(j)->setPosition(watchPos);
		numSpr.at(j)->setScale(0.6f);
		this->addChild(numSpr.at(j), 2);
	}
	
	ramdomBreak();            //breakNumの数だけランダムで数字を壊す

	//汚れ
	dirtWatch = Sprite::create("GameScene/clockThree.png");
	dirtWatch->setPosition(watchPos);
	dirtWatch->setScale(0.6f);
	this->addChild(dirtWatch, 3);


	//つまみ
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize.width * 0.96f, watchPos.y));
	_knob->setScale(0.5f);
	this->addChild(_knob,0);

	//短針
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	this->addChild(_shortHand,4);

	//長針
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	this->addChild(_longHand,5);

	//秒針
	_secondHand = SecondHand::create();
	_secondHand->setPosition(watchPos);
	this->addChild(_secondHand, 8);

	//光の反射
	glassShine = Sprite::create("GameScene/clockFour.png");
	glassShine->setPosition(watchPos);
	glassShine->setScale(0.6f);
	this->addChild(glassShine,9);

	//Playerクラス
	_player = Player::create();
	this->addChild(_player);

	//EnemyManagerクラス
	_enemyManager = EnemyManager::create(circle - 1);
	this->addChild(_enemyManager,9);

	this->scheduleUpdate();

	return true;
}

void WatchLayer::update(float delta)
{
	_secondHand->setRotation(_secondHand->getRotation() + 0.1f);
	if (_secondHand->getRotation() >= 360.0f)
	{
		_secondHand->setRotation(_secondHand->getRotation() - 360.0f);
	}
}

void WatchLayer::ramdomBreak()
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> breakPosNum(0, 11);
	while (true)
	{
		actingBreak = breakPosNum(mt);
		if (breakCheck[actingBreak] == true)
		{
			breakCheck[actingBreak] = false;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak.png", actingBreak + 1);
			numSpr.at(actingBreak)->setTexture(breakNoNum->getCString());
			breakNumCheck++;
		}
		if (breakNum == breakNumCheck) break;
	}
}