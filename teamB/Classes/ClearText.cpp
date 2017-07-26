#include "ClearText.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

ClearText *ClearText::create(int HScore, int score, int nowM, int nowS, bool highScoreC)
{
	ClearText *pRet = new ClearText();
	if (pRet && pRet->init(HScore,score,nowM,nowS,highScoreC))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ClearText::init(int HScore, int score, int nowM, int nowS, bool highScoreC)
{
	if (!Node::init()) return false;

	auto layer = ((WatchLayer*)(this->getParent()));
	highScorePoint = HScore;
	scorePoint = score;
	bonusPoint = (999 - (int)(((nowM * 100) + (nowS))*0.1f));
	sCheck = highScoreC;
	bonusGate = false;

	nowScore = Label::createWithTTF("1", "fonts/PixelMplus12-Bold.ttf", 96);
	String* nowScoreStr = String::createWithFormat("%06d",scorePoint);
	nowScore->setString(nowScoreStr->getCString());
	nowScore->setPosition(designResolutionSize.width*0.4f,designResolutionSize.height*0.3f);
	nowScore->setColor(Color3B::WHITE);
	this->addChild(nowScore);

	scoreChar = Label::createWithTTF("Score", "fonts/PixelMplus12-Bold.ttf", 40);
	scoreChar->setPosition(nowScore->getPositionX() - 100, nowScore->getPositionY() + 70);
	scoreChar->setColor(Color3B::WHITE);
	this->addChild(scoreChar);

	CallFunc* callBTime = CallFunc::create([=] { timeBonusDisplay(); });
	CallFunc* callGateOpen = CallFunc::create([=] { bonusGate = true; });
	Sequence* seq = Sequence::create(DelayTime::create(1.0f), callBTime, DelayTime::create(1.0f), callGateOpen, nullptr);
	this->runAction(seq);

	this->scheduleUpdate();
	return true;
}

void ClearText::update(float delta)
{
	if (bonusPoint > 0 && bonusGate)
	{
		bonusPoint--;
		scorePoint++;

		String* timeBonusStr = String::createWithFormat("+%d", bonusPoint);
		timeBonus->setString(timeBonusStr->getCString());
		String* nowScoreStr = String::createWithFormat("%06d", scorePoint);
		nowScore->setString(nowScoreStr->getCString());

	}
	if (bonusPoint == 0 && bonusGate)
	{
		this->scheduleOnce(schedule_selector(ClearText::highScoreDisplay), 1.0f);
		bonusGate = false;
	}
}

//タイムボーナス表示
void ClearText::timeBonusDisplay()
{
	auto layer = ((WatchLayer*)(this->getParent()));

	timeBonus = Label::createWithTTF("1", "fonts/PixelMplus12-Bold.ttf", 60);
	String* timeBonusStr = String::createWithFormat("+%d", bonusPoint);
	timeBonus->setString(timeBonusStr->getCString());
	timeBonus->setPosition(nowScore->getPositionX() + 250, nowScore->getPositionY());
	timeBonus->setColor(Color3B::WHITE);
	this->addChild(timeBonus);

	bonusChar = Label::createWithTTF("TimeBonus", "fonts/PixelMplus12-Bold.ttf", 40);
	bonusChar->setPosition(timeBonus->getPositionX(), timeBonus->getPositionY() + 70);
	bonusChar->setColor(Color3B::WHITE);
	this->addChild(bonusChar);

	layer->_player->skipTap = true;
}

//ハイスコア表示
void ClearText::highScoreDisplay(float delta)
{
	auto layer = ((WatchLayer*)(this->getParent()));

	highScore = Label::createWithTTF("1", "fonts/PixelMplus12-Bold.ttf", 128);
	String* highScoreStr = String::createWithFormat("%06d", highScorePoint);
	highScore->setString(highScoreStr->getCString());
	highScore->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	highScore->setColor(Color3B::WHITE);
	this->addChild(highScore);

	if (sCheck == true)
	{
		Sprite* highSpr = Sprite::create("GameScene/high.png");
		highSpr->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.65f);
		highSpr->setScale(0.6f);
		this->addChild(highSpr);
	}
	layer->createModoru();

}
//スキップ
void ClearText::skip()
{
	scorePoint += bonusPoint;
	bonusPoint = 0;
	String* timeBonusStr = String::createWithFormat("+%d", bonusPoint);
	timeBonus->setString(timeBonusStr->getCString());
	String* nowScoreStr = String::createWithFormat("%06d", scorePoint);
	nowScore->setString(nowScoreStr->getCString());

}