#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	effect = EffectManager::create();
	this->addChild(effect, 10);

	//背景仮置き
	backOne = Sprite::create("GameScene/back.png");
	backOne->setPosition(designResolutionSize*0.5f);
	this->addChild(backOne, 0);
	Sprite* hagu = Sprite::create("GameScene/hagu.png");
	hagu->setPosition(designResolutionSize);
	hagu->setScale(2.0f);
	this->addChild(hagu, 1);
	backTwo = Sprite::create("GameScene/back2.png");
	backTwo->setPosition(designResolutionSize*0.5f);
	this->addChild(backTwo, -2);

	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 3;           //壊す数字の数  11以上にしないように
	maxNumberHP = 10.0f;       //数字の最大HP初期化
	repairScore = 1.0f;
	repairBonusScore = 2.0f;

	for (int t = 0; t < circleNum; t++)
	{
		breakCheck[t] = true;        //数字が壊れてるかどうかの初期化
		numberHP[t] = maxNumberHP;        //数字のHP初期化
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
	for (int i = 0; i < circleNum; i++)
	{
		fairyGate.push_back(FairyGate::create());
		fairyGate.at(i)->setPosition(Vec2(designResolutionSize.width*0.5f + radius*cos(M_PI / 180 * (90 - 360 * i / circleNum)),
			                              designResolutionSize.height*0.5f + radius*sin(M_PI / 180 * (90 - 360 * i / circleNum))));
		fairyGate.at(i)->setScale(0.15f);
		this->addChild(fairyGate.at(i),5);
	}
	//数字を表示
	for (int j = 0; j < circleNum; j++)
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
	_enemyManager = EnemyManager::create(circleNum - 1);
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

//数字をbreakNumの数分壊す
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
			numberHP[actingBreak] = 0.0f;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak.png", actingBreak + 1);
			numSpr.at(actingBreak)->setTexture(breakNoNum->getCString());
			actingBreak++;
			if (actingBreak > 11)
			{
				actingBreak = 0;
			}
			fairyGate.at(actingBreak)->setTexture("GameScene/badVortex.png");
			breakNumCheck++;
		}
		if (breakNum == breakNumCheck) break;
	}
}

//数字修復&クリアしたかどうか
void WatchLayer::repairNumber(int num,bool bonus)
{
	if (!bonus)
	{
		numberHP[num] += repairScore;
	}
	else
	{
		numberHP[num] += repairBonusScore;
	}

	if (numberHP[num] >= maxNumberHP)
	{
		breakCheck[num] = true;
		String* repairNumStr = String::createWithFormat("GameScene/clockTwo-%d.png", num + 1);
		numSpr.at(num)->setTexture(repairNumStr->getCString());
		int repairNum = num;

		repairNum++;
		if (repairNum > 11)
		{
			repairNum = 0;
		}
		fairyGate.at(repairNum)->setTexture("GameScene/goodVortex.png");

		for (int g = 0; g < circleNum; g++)
		{
			if (breakCheck[g] == false)
			{
				return;
			}
		}
		log("OK!");  //ここにクリア処理
	}
	else
	{

	}
}

//妖精生成演出&敵生成
void WatchLayer::adventGateMotion(int GatePos)
{
	ScaleTo* bigGate = ScaleTo::create(0.5f, 0.4f);
	CallFunc* gateSpeedUP = CallFunc::create([=]
	{
		fairyGate.at(GatePos)->speed = 10.0f;
	});
	CallFunc* fairyCreate = CallFunc::create([=]
	{
		_enemyManager->fairyCreate(GatePos);
	});
	CallFunc* gateSpeedDOWN = CallFunc::create([=]
	{
		fairyGate.at(GatePos)->speed = 2.0f;
	});
	ScaleTo* smallGate = ScaleTo::create(0.5f, 0.15f);
	Sequence* seq = Sequence::create(gateSpeedUP,
		                             bigGate,
		                             DelayTime::create(1.5f), 
		                             fairyCreate,
		                             DelayTime::create(0.5f),
		                             gateSpeedDOWN,
		                             smallGate, 
		                             nullptr);
	fairyGate.at(GatePos)->runAction(seq);
}