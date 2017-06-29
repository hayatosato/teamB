#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	masterHand = false;

	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 1;           //‰ó‚·”š‚Ì”  11ˆÈã‚É‚µ‚È‚¢‚æ‚¤‚É
	nowBreakNum = 0;
	maxNumberHP = 10.0f;       //”š‚ÌÅ‘åHP‰Šú‰»
	repairScore = 1.0f;
	repairBonusScore = 2.0f;
	UIPos = Vec2(designResolutionSize*0.0f);
	timePos = Vec2(designResolutionSize.width*0.25f, designResolutionSize.height*0.9f);

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
	this->addChild(effect, 10);

	//”ç
	backOne = Sprite::create("GameScene/kawa.png");
	backOne->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.7f);
	this->addChild(backOne, 0);
	backTwo = Sprite::create("GameScene/kawa.png");
	backTwo->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.3f);
	this->addChild(backTwo, 0);

	for (int t = 0; t < circleNum; t++)
	{
		breakCheck[t] = true;        //”š‚ª‰ó‚ê‚Ä‚é‚©‚Ç‚¤‚©‚Ì‰Šú‰»
		numberHP[t] = maxNumberHP;        //”š‚ÌHP‰Šú‰»
	}
	//Œv‚ÌˆÊ’u
	Vec2 watchPos = designResolutionSize * 0.5f;

	//Œv
	_watchSprite = Sprite::create("GameScene/clockOne.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(0.6f);
	this->addChild(_watchSprite,1);

	radius = (_watchSprite->getContentSize().width*0.5f)*0.6f;

	//—d¸”­¶’n“_İ’è&ƒQ[ƒg‰æ‘œ”z’u
	for (int i = 0; i < circleNum; i++)
	{
		fairyGate.push_back(FairyGate::create());
		fairyGate.at(i)->setPosition(Vec2(designResolutionSize.width*0.5f + radius*cos(M_PI / 180 * (90 - 360 * i / circleNum)),
			                              designResolutionSize.height*0.5f + radius*sin(M_PI / 180 * (90 - 360 * i / circleNum))));
		fairyGate.at(i)->setScale(0.15f);
		fairyGate.at(i)->setVisible(false);
		this->addChild(fairyGate.at(i),5);
	}
	//”š‚ğ•\¦
	for (int j = 0; j < circleNum; j++)
	{
		String* noNum = String::createWithFormat("GameScene/clockTwo-%d.png", j + 1);
		numSpr.push_back(Sprite::create(noNum->getCString()));
		numSpr.at(j)->setPosition(watchPos);
		numSpr.at(j)->setScale(0.6f);
		this->addChild(numSpr.at(j), 2);
		//numSpr.at(j)->setOpacity(200);
	}
	
	//‰˜‚ê
	dirtWatch = Sprite::create("GameScene/clockThree.png");
	dirtWatch->setPosition(watchPos);
	dirtWatch->setScale(0.6f);
	this->addChild(dirtWatch, 3);

	//‚Â‚Ü‚İ
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize.width * 0.96f, watchPos.y));
	_knob->setScale(0.5f);
	this->addChild(_knob,0);

	//’Zj
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	this->addChild(_shortHand,4);

	//’·j
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	this->addChild(_longHand,5);

	//•bj
	_secondHand = SecondHand::create();
	_secondHand->setPosition(watchPos);
	this->addChild(_secondHand, 8);

	_shortHand->setVisible(false);
	_longHand->setVisible(false);
	_secondHand->setVisible(false);

	//Œõ‚Ì”½Ë
	glassShine = Sprite::create("GameScene/clockFour.png");
	glassShine->setPosition(watchPos);
	glassShine->setScale(0.6f);
	this->addChild(glassShine,9);

	//PlayerƒNƒ‰ƒX
	_player = Player::create();
	this->addChild(_player);

	//EnemyManagerƒNƒ‰ƒX
	_enemyManager = EnemyManager::create(circleNum - 1);
	this->addChild(_enemyManager,9);

	//ƒNƒŠƒA‰æ‘œ
	clear = Clear::create();
	clear->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*-0.2f);
	this->addChild(clear, 13);

	//ŠÔ
	timeLabel = TimeLabel::create();
	timeLabel->setPosition(timePos.x,timePos.y+200);
	this->addChild(timeLabel, 10);

	//ŠÔ‚Ì˜g
	timeWaku = Sprite::create("GameScene/timeWaku.png");
	timeWaku->setPosition(timePos.x, timePos.y + 200.0f);
	this->addChild(timeWaku, 9);

	//UI
	UI = UIManager::create(nowBreakNum , breakNum);
	UI->setPosition(UIPos.x,UIPos.y + 200.0f);
	this->addChild(UI,10);

	this->scheduleUpdate();

	return true;
}

void WatchLayer::update(float delta)
{
	timeWaku->setPosition(timeLabel->getPosition());


	if (!masterHand) return;
	//•bj‚Ì‰ñ“]
	_secondHand->setRotation(_secondHand->getRotation() + 0.1f);
	if (_secondHand->getRotation() >= 360.0f)
	{
		_secondHand->setRotation(_secondHand->getRotation() - 360.0f);
	}
}

//”š‚ğbreakNum‚Ì”•ª‰ó‚·
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

//”šC•œ&ƒNƒŠƒA‚µ‚½‚©‚Ç‚¤‚©
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
		fairyGate.at(repairNum)->setVisible(false);
		effect->numberShining(fairyGate.at(repairNum)->getPosition());
		for (int g = 0; g < circleNum; g++)
		{
			if (breakCheck[g] == false)
			{
				return;
			}
		}
		log("OK!");  //‚±‚±‚ÉƒNƒŠƒAˆ—
		end();
	}
	else
	{
		//”š‚ª‚¾‚ñ‚¾‚ñ¡‚Á‚Ä‚¢‚­
		if (numberHP[num] >= 0 && numberHP[num] <= Calculation::senF(0.0f,maxNumberHP,0.1f))
		{
			//‘Ì—Í‚ª0`10%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1,9);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.11f) && 
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.2f))
		{
			//‘Ì—Í‚ª11`20%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 8);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if(numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.21f) &&
			    numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.3f))
		{
			//‘Ì—Í‚ª21`30%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 7);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.31f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.4f))
		{
			//‘Ì—Í‚ª31`40%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 6);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.41f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.5f))
		{
			//‘Ì—Í‚ª41`50%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 5);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.51f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.6f))
		{
			//‘Ì—Í‚ª51`60%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 4);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.61f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.7f))
		{
			//‘Ì—Í‚ª61`70%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 3);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.71f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.8f))
		{
			//‘Ì—Í‚ª71`80%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 2);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.81f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.9f))
		{
			//‘Ì—Í‚ª81`90%‚Ì
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak-%d.png", num + 1, 1);
			numSpr.at(num)->setTexture(breakNoNum->getCString());
		}
	}
}

//—d¸¶¬‰‰o&“G¶¬
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
	fairyGate.at(GatePos)->runAction(seq);
}

//‹N“®
void WatchLayer::start()
{
	masterHand = true;
	_player->masterTap = true;
	_enemyManager->masterFairy = true;
	timeLabel->masterTime();
}

//n‚Ü‚è‰‰oŠJn
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

	countThree->runAction(seqThree);

	this->scheduleOnce(schedule_selector(WatchLayer::cTwo), 1.0f);
	this->scheduleOnce(schedule_selector(WatchLayer::cOne), 2.0f);

}

//2‚Ì“®‚«
void WatchLayer::cTwo(float delta)
{
	scaleTo = ScaleTo::create(0.75f, 1.0f);
	dTwo = CallFunc::create([=]
	{
		countTwo->setVisible(false);
	});
	seqTwo = Sequence::create(scaleTo, DelayTime::create(0.25f), dTwo, nullptr);

	countTwo->runAction(seqTwo);
}

//3‚Ì“®‚«
void WatchLayer::cOne(float delta)
{
	scaleTo = ScaleTo::create(0.75f, 1.0f);
	dOne = CallFunc::create([=]
	{
		countOne->setVisible(false);
		start();
	});
	seqOne = Sequence::create(scaleTo, DelayTime::create(0.25f), dOne, nullptr);

	countOne->runAction(seqOne);
}

//j‚Æ”š‚ğŒ©‚¹‚é
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

void WatchLayer::end()
{
	masterHand = false;
	_player->masterTap = false;
	_enemyManager->masterFairy = false;
	timeLabel->stopTime();

	FadeIn* BfadeIn = FadeIn::create(0.7f);
	blackBack->runAction(BfadeIn);

	Sequence* clearSeq = Sequence::create(
		                                  DelayTime::create(0.5f),
		                                  MoveTo::create(1.0f, designResolutionSize*0.5f),
		                                  DelayTime::create(1.0f),
		                                  MoveTo::create(1.5f, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.8f)),
		                                  nullptr
		                                 );
	clear->runAction(clearSeq);
}