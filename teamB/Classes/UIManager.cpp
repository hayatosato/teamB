#include "UIManager.h"
#include "WatchLayer.h"
#include "MultiResolution.h"
#include "Calculation.h"

UIManager *UIManager::create(int breakNum, int breakNumMax)
{
	UIManager *pRet = new UIManager();
	if (pRet && pRet->init(breakNum, breakNumMax))
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


bool UIManager::init(int breakNum, int breakNumMax)
{
	if (!Node::init()) return false;

	breakNumBasePos = Vec2(designResolutionSize.width*0.55f, designResolutionSize.height*0.9f);

	gaugeOne = Sprite::create("GameScene/gauge1.png");
	gaugeOne->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	gaugeOne->setPosition(breakNumBasePos);
	this->addChild(gaugeOne,0);

	breakMeter = Sprite::create("GameScene/gauge2.png");
	breakMeter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	breakMeter->setPosition(breakNumBasePos);
	breakMeter->setScaleX(Calculation::senF(0.0f,1.0f, (float)breakNum/(float)breakNumMax));
	this->addChild(breakMeter, 1);

	gaugeTwo = Sprite::create("GameScene/gauge3.png");
	gaugeTwo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	gaugeTwo->setPosition(breakNumBasePos);
	this->addChild(gaugeTwo, 2);

	breakLabel = Label::createWithTTF("1", "fonts/Jiyucho.ttf",32);
	String* breakStr = String::createWithFormat("%d/%d", breakNum, breakNumMax);
	breakLabel->setString(breakStr->getCString());
	breakLabel->setPosition(breakNumBasePos.x + (gaugeOne->getContentSize().width*0.5f), breakNumBasePos.y);
	breakLabel->setColor(Color3B::BLACK);
	this->addChild(breakLabel, 3);

	return true;
}

void UIManager::breakChangeGauge(float nowRatio, float ratioMax)
{
	breakMeter->setScaleX(Calculation::senF(0.0f, 1.0f, nowRatio/ ratioMax));
	String* breakStr = String::createWithFormat("%d/%d", (int)nowRatio, (int)ratioMax);
	breakLabel->setString(breakStr->getCString());


}