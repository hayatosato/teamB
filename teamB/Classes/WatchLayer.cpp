#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	masterHand = false;

	effect = EffectManager::create();
	this->addChild(effect, 10);

	backDesk = Sprite::create("GameScene/gameSceneBack.png");
	backDesk->setPosition(designResolutionSize*0.5f);
	this->addChild(backDesk,-1);

	//皮
	backOne = Sprite::create("GameScene/kawa.png");
	backOne->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.7f);
	this->addChild(backOne, 0);
	backTwo = Sprite::create("GameScene/kawa.png");
	backTwo->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.3f);
	this->addChild(backTwo, 0);

	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 5;           //壊す数字の数  11以上にしないように
	nowBreakNum = 0;
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

	//時間
	timeLabel = TimeLabel::create();
	timeLabel->setPosition(designResolutionSize.width*0.25f, designResolutionSize.height*0.9f);
	this->addChild(timeLabel, 10);

	timeWaku = Sprite::create("GameScene/timeWaku.png");
	timeWaku->setPosition(timeLabel->getPosition());
	this->addChild(timeWaku, 9);

	//UI
	UI = UIManager::create(nowBreakNum , breakNum);
	this->addChild(UI,10);

	this->scheduleUpdate();

	return true;
}

void WatchLayer::update(float delta)
{
	if (!masterHand) return;
	//秒針の回転
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
		nowBreakNum++;
		UI->breakChangeGauge((float)nowBreakNum , (float)breakNum);
		String* repairNumStr = String::createWithFormat("GameScene/clockTwo-%d.png", num + 1);
		numSpr.at(num)->setTexture(repairNumStr->getCString());
		int repairNum = num;

		repairNum++;
		if (repairNum > 11)
		{
			repairNum = 0;
		}
		fairyGate.at(repairNum)->setTexture("GameScene/goodVortex.png");
		effect->numberShining(fairyGate.at(repairNum)->getPosition());
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
		//数字がだんだん治っていく
		if (numberHP[num] >= 0 && numberHP[num] <= Calculation::senF(0.0f,maxNumberHP,0.1f))
		{
			//体力が0〜10%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1,9);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.11f) && 
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.2f))
		{
			//体力が11〜20%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 8);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if(numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.21f) &&
			    numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.3f))
		{
			//体力が21〜30%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 7);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.31f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.4f))
		{
			//体力が31〜40%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 6);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.41f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.5f))
		{
			//体力が41〜50%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 5);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.51f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.6f))
		{
			//体力が51〜60%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 4);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.61f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.7f))
		{
			//体力が61〜70%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 3);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.71f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.8f))
		{
			//体力が71〜80%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 2);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.81f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.9f))
		{
			//体力が81〜90%の時
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 1);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.91f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.99f))
		{
			//体力が91〜99%の時
			//今のところ保留
		}

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

//起動
void WatchLayer::start()
{
	masterHand = true;
	_player->masterTap = true;
	_enemyManager->masterFairy = true;
	timeLabel->masterTime();
}