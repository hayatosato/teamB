#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	masterHand = false;
	timeScore = UserDefault::getInstance();
	if (timeScore->getIntegerForKey("seconds") == 0 &&
		timeScore->getIntegerForKey("minute") == 0)
	{
		timeScore->setIntegerForKey("seconds", 99);
		timeScore->setIntegerForKey("minute", 99);
	}

	//ハイスコアリセット
	//timeScore->setIntegerForKey("seconds", 0);
	//timeScore->setIntegerForKey("minute", 0);


	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 3;           //壊す数字の数  11以上にしないように
	nowBreakNum = 0;
	maxNumberHP = 10.0f;       //数字の最大HP初期化
	repairScore = 1.0f;
	repairBonusScore = 2.0f;
	UIPos = Vec2(designResolutionSize*0.0f);
	timePos = Vec2(designResolutionSize.width*0.25f, designResolutionSize.height*0.9f);
	highScoreCheck = false;

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/titleMusic.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/gameSceneMusic2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/titleTap.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/count.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/numR2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/numRMax.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/death.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/deathWall.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/powerUP.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Ride.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Gush.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/titleMusic.mp3", true);


	title = Title::create();
	title->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.6f);
	this->addChild(title, 12);

	navi = TextNavi::create();
	navi->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f);
	navi->setScale(0.5f);
	this->addChild(navi, 12);

	blackBack = Sprite::create("GameScene/kuro.png");
	blackBack->setPosition(designResolutionSize*0.5f);
	this->addChild(blackBack, 11);

	countThree = Sprite::create("GameScene/count3.png");
	countThree->setAnchorPoint(Point(0.25f,0.5f));
	countThree->setPosition(designResolutionSize*0.5f);
	countThree->setScale(0.0f);
	this->addChild(countThree, 11);

	countTwo = Sprite::create("GameScene/count2.png");
	countTwo->setAnchorPoint(Point(0.75f, 0.5f));
	countTwo->setPosition(designResolutionSize*0.5f);
	countTwo->setScale(0.0f);
	this->addChild(countTwo, 11);

	countOne = Sprite::create("GameScene/count1.png");
	countOne->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	countOne->setScale(0.0f);
	this->addChild(countOne, 11);

	effect = EffectManager::create();
	this->addChild(effect, 18);

	//皮
	backOne = Sprite::create("GameScene/kawa.png");
	backOne->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.7f);
	this->addChild(backOne, 0);
	backTwo = Sprite::create("GameScene/kawa.png");
	backTwo->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.3f);
	this->addChild(backTwo, 0);

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
		fairyGate.at(i)->setVisible(false);
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
		//numSpr.at(j)->setOpacity(200);
	}
	
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

	_shortHand->setVisible(false);
	_longHand->setVisible(false);
	_secondHand->setVisible(false);

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

	//クリア画像
	clear = Clear::create();
	clear->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*-0.2f);
	this->addChild(clear, 13);

	//時間
	timeLabel = TimeLabel::create();
	timeLabel->setPosition(timePos.x,timePos.y+200);
	this->addChild(timeLabel, 10);

	//時間の枠
	timeWaku = Sprite::create("GameScene/timeWaku.png");
	timeWaku->setPosition(timePos.x, timePos.y + 200.0f);
	this->addChild(timeWaku, 9);

	//UI
	UI = UIManager::create();
	UI->setPosition(UIPos.x,UIPos.y + 200.0f);
	this->addChild(UI,10);

	this->scheduleUpdate();

	return true;
}

void WatchLayer::update(float delta)
{
	timeWaku->setPosition(timeLabel->getPosition());


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
			fairyGate.at(actingBreak)->setVisible(true);
			breakNumCheck++;
		}
		if (breakNum == breakNumCheck) break;
	}
}

//数字修復&クリアしたかどうか
void WatchLayer::repairNumber(int num,bool bonus,int fairyScore,Vec2 fairyPos)
{
	if (!bonus)
	{
		numberHP[num] += repairScore;
		plusScore(fairyScore);
		effect->pointGet(fairyPos, fairyScore,bonus);
	}
	else
	{
		numberHP[num] += repairBonusScore;
		plusScore(fairyScore*2);
		effect->pointGet(fairyPos, fairyScore*2,bonus);
	}

	if (numberHP[num] >= maxNumberHP)
	{
		breakCheck[num] = true;
		effectPlayMusic(4);
		nowBreakNum++;
		String* repairNumStr = String::createWithFormat("GameScene/clockTwo-%d.png", num + 1);
		numSpr.at(num)->setTexture(repairNumStr->getCString());
		int repairNum = num;

		repairNum++;
		if (repairNum > 11)
		{
			repairNum = 0;
		}
		fairyGate.at(repairNum)->setTexture("GameScene/goodVortex.png");
		fairyGate.at(repairNum)->setVisible(false);
		effect->numberShining(fairyGate.at(repairNum)->getPosition());
		for (int g = 0; g < circleNum; g++)
		{
			if (breakCheck[g] == false)
			{
				return;
			}
		}
		log("OK!");  //ここにクリア処理
		end();
	}
	else
	{
		effectPlayMusic(3);
		int clockTwoNum;

		//数字がだんだん治っていく
		if (numberHP[num] >= 0 && numberHP[num] <= Calculation::senF(0.0f,maxNumberHP,0.1f))
		{
			//体力が0～10%の時
			clockTwoNum = 9;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1,clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.11f) && 
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.2f))
		{
			//体力が11～20%の時
			clockTwoNum = 8;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if(numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.21f) &&
			    numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.3f))
		{
			//体力が21～30%の時
			clockTwoNum = 7;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.31f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.4f))
		{
			//体力が31～40%の時
			clockTwoNum = 6;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.41f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.5f))
		{
			//体力が41～50%の時
			clockTwoNum = 5;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.51f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.6f))
		{
			//体力が51～60%の時
			clockTwoNum = 4;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.61f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.7f))
		{
			//体力が61～70%の時
			clockTwoNum = 3;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.71f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.8f))
		{
			//体力が71～80%の時
			clockTwoNum = 2;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.81f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.9f))
		{
			//体力が81～90%の時
			clockTwoNum = 1;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, clockTwoNum);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		effect->numWave(num + 1, clockTwoNum);
	}
}

//妖精生成演出&敵生成
void WatchLayer::adventGateMotion(int GatePos)
{
	fairyGate.at(GatePos)->setVisible(true);
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

	CallFunc* v = CallFunc::create([=] 
	{
		fairyGate.at(GatePos)->setVisible(false);
	});

	Sequence* seq = Sequence::create(gateSpeedUP,
		                             bigGate,
		                             DelayTime::create(1.5f), 
		                             fairyCreate,
		                             DelayTime::create(0.5f),
		                             gateSpeedDOWN,
		                             smallGate,
		                             v,
		                             nullptr);

	effectPlayMusic(9);
	fairyGate.at(GatePos)->runAction(seq);
}

//起動
void WatchLayer::start()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/gameSceneMusic2.mp3", true);
	masterHand = true;
	_player->masterTap = true;
	_enemyManager->masterFairy = true;
	timeLabel->masterTime();
}

//始まり演出開始
void WatchLayer::startCountDown()
{
	timeMove = MoveTo::create(0.5f, timePos);
	UIMove = MoveTo::create(0.5f, UIPos);
	timeLabel->runAction(timeMove);
	UI->runAction(UIMove);

	ramdomBreak();
	showingNeedle();

	scaleTo = ScaleTo::create(0.75f, 1.0f);
	dThree = CallFunc::create([=]
	{
		countThree->setVisible(false);
	});

	seqThree = Sequence::create(scaleTo,DelayTime::create(0.25f), dThree, nullptr);


	effectPlayMusic(2);
	countThree->runAction(seqThree);

	this->scheduleOnce(schedule_selector(WatchLayer::cTwo), 1.0f);
	this->scheduleOnce(schedule_selector(WatchLayer::cOne), 2.0f);

}

//2の動き
void WatchLayer::cTwo(float delta)
{
	scaleTo = ScaleTo::create(0.75f, 1.0f);
	dTwo = CallFunc::create([=]
	{
		countTwo->setVisible(false);
	});
	seqTwo = Sequence::create(scaleTo, DelayTime::create(0.25f), dTwo, nullptr);

	effectPlayMusic(2);
	countTwo->runAction(seqTwo);
}

//1の動き
void WatchLayer::cOne(float delta)
{
	scaleTo = ScaleTo::create(0.75f, 1.0f);
	dOne = CallFunc::create([=]
	{
		countOne->setVisible(false);
		start();
	});
	seqOne = Sequence::create(scaleTo, DelayTime::create(0.25f), dOne, nullptr);

	effectPlayMusic(2);
	countOne->runAction(seqOne);
}

//針と数字を見せる
void WatchLayer::showingNeedle()
{
	for (int i = 0; i < circleNum; i++)
	{
		numSpr.at(i)->setOpacity(0);
		FadeIn* fadeIn = FadeIn::create(1.0f);
		numSpr.at(i)->runAction(fadeIn);
	}
	_shortHand->setVisible(true);
	_longHand->setVisible(true);
	_secondHand->setVisible(true);
}

//終わり
void WatchLayer::end()
{
	masterHand = false;
	_player->masterTap = false;
	_enemyManager->masterFairy = false;
	timeLabel->stopTime();

	//スコアの繁栄
	if (timeScore->getIntegerForKey("minute") > timeLabel->minute)
	{
		timeScore->setIntegerForKey("seconds", timeLabel->seconds);
		timeScore->setIntegerForKey("minute", timeLabel->minute);
		highScoreCheck = true;
	}
	else if (timeScore->getIntegerForKey("minute") == timeLabel->minute)
	{
		if (timeScore->getIntegerForKey("seconds") > timeLabel->seconds)
		{
			timeScore->setIntegerForKey("seconds", timeLabel->seconds);
			timeScore->setIntegerForKey("minute", timeLabel->minute);
			highScoreCheck = true;
		}
	}

	FadeIn* BfadeIn = FadeIn::create(0.7f);
	blackBack->runAction(BfadeIn);

	Sequence* clearSeq = Sequence::create(
		                                  DelayTime::create(0.5f),
		                                  MoveTo::create(1.0f, designResolutionSize*0.5f),
		                                  DelayTime::create(1.0f),
		                                  MoveTo::create(1.5f, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.8f)),
		                                  DelayTime::create(0.5f),
		                                  CallFunc::create([=] {
		                                                         ClearText* clearText = ClearText::create(timeLabel->minute,timeLabel->seconds,timeScore->getIntegerForKey("minute"), timeScore->getIntegerForKey("seconds"),highScoreCheck);
		                                                         this->addChild(clearText, 13);
	                                                           }),
		                                  DelayTime::create(1.0f),
										  CallFunc::create([=] {
																   Sprite* modoru = Sprite::create("GameScene/modoru.png");
																   modoru->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f);
																   modoru->setScale(0.7f);
																   this->addChild(modoru, 13);
																   _player->retryTap = true;
															   }),
		                                  nullptr
		                                 );
	clear->runAction(clearSeq);
}

void WatchLayer::stopMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void WatchLayer::effectPlayMusic(int musicNum)
{
	switch (musicNum)
	{
	case 1:
		SimpleAudioEngine::getInstance()->playEffect("Music/titleTap.wav", false);
		break;
	case 2:
		SimpleAudioEngine::getInstance()->playEffect("Music/count.wav", false);
		break;
	case 3:
		SimpleAudioEngine::getInstance()->playEffect("Music/numR2.wav", false);
		break;
	case 4:
		SimpleAudioEngine::getInstance()->playEffect("Music/numRMax.wav", false);
		break;
	case 5:
		SimpleAudioEngine::getInstance()->playEffect("Music/death.wav", false);
		break;
	case 6:
		SimpleAudioEngine::getInstance()->playEffect("Music/deathWall.wav", false);
		break;
	case 7:
		SimpleAudioEngine::getInstance()->playEffect("Music/powerUP.wav", false);
		break;
	case 8:
		SimpleAudioEngine::getInstance()->playEffect("Music/Ride.wav", false);
		break;
	case 9:
		SimpleAudioEngine::getInstance()->playEffect("Music/Gush.wav", false);
		break;
	}
}

//スコアを足す処理
void WatchLayer::plusScore(int upScore)
{
	UI->score += upScore;
}