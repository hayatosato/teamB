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

	//”ç
	backOne = Sprite::create("GameScene/kawa.png");
	backOne->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.7f);
	this->addChild(backOne, 0);
	backTwo = Sprite::create("GameScene/kawa.png");
	backTwo->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.3f);
	this->addChild(backTwo, 0);

	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 5;           //‰ó‚·”š‚Ì”  11ˆÈã‚É‚µ‚È‚¢‚æ‚¤‚É
	nowBreakNum = 0;
	maxNumberHP = 10.0f;       //”š‚ÌÅ‘åHP‰Šú‰»
	repairScore = 1.0f;
	repairBonusScore = 2.0f;

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
	}
	
	ramdomBreak();            //breakNum‚Ì”‚¾‚¯ƒ‰ƒ“ƒ_ƒ€‚Å”š‚ğ‰ó‚·

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

	//ŠÔ
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
		effect->numberShining(fairyGate.at(repairNum)->getPosition());
		for (int g = 0; g < circleNum; g++)
		{
			if (breakCheck[g] == false)
			{
				return;
			}
		}
		log("OK!");  //‚±‚±‚ÉƒNƒŠƒAˆ—
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
		else if (numberHP[num] >= Calculation::senF(0.0f, maxNumberHP, 0.91f) &&
			     numberHP[num] <= Calculation::senF(0.0f, maxNumberHP, 0.99f))
		{
			//‘Ì—Í‚ª91`99%‚Ì
			//¡‚Ì‚Æ‚±‚ë•Û—¯
		}

	}
}

//—d¸¶¬‰‰o&“G¶¬
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

//‹N“®
void WatchLayer::start()
{
	masterHand = true;
	_player->masterTap = true;
	_enemyManager->masterFairy = true;
	timeLabel->masterTime();
}