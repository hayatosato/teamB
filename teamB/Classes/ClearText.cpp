#include "ClearText.h"
#include "WatchLayer.h"
#include "MultiResolution.h"

ClearText *ClearText::create(int nowM, int nowS, int highM, int highS, bool highScoreC)
{
	ClearText *pRet = new ClearText();
	if (pRet && pRet->init(nowM,nowS,highM,highS,highScoreC))
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


bool ClearText::init(int nowM, int nowS, int highM, int highS, bool highScoreC)
{
	if (!Node::init()) return false;

	auto layer = ((WatchLayer*)(this->getParent()));

	nowScore = Label::createWithTTF("1", "fonts/Jiyucho.ttf", 96);
	String* nowScoreStr = String::createWithFormat("%02d:%02d", nowM, nowS);
	nowScore->setString(nowScoreStr->getCString());
	nowScore->setPosition(designResolutionSize.width*0.5f,designResolutionSize.height*0.3f);
	nowScore->setColor(Color3B::WHITE);
	this->addChild(nowScore);

	highScore = Label::createWithTTF("1", "fonts/Jiyucho.ttf", 128);
	String* highScoreStr = String::createWithFormat("%02d:%02d", highM, highS);
	highScore->setString(highScoreStr->getCString());
	highScore->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	highScore->setColor(Color3B::WHITE);
	this->addChild(highScore);

	if (highScoreC == true)
	{
		Sprite* highSpr = Sprite::create("GameScene/high.png");
		highSpr->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.65f);
		highSpr->setScale(0.6f);
		this->addChild(highSpr);
	}

	return true;
}