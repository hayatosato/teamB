#include "PointLabel.h"

//PointLabel *PointLabel::create(int pointNum)
//{
//	PointLabel *pRet = new PointLabel();
//	if (pRet && pRet->init(pointNum))
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else {
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}

bool PointLabel::init()
{
	if (!Label::init())
	{
		return false;
	}
	colorCount = 3;
	bonusColor = false;
	this->initWithTTF("1", "fonts/Hayatonumfont-Regular.ttf", 40);
	//this->setColor(Color3B(209, 207, 207));
	this->setColor(Color3B(170, 170, 170));

	FadeOut* fadeOut = FadeOut::create(0.7f);
	CallFunc* callE = CallFunc::create([=] {erase();});
	Sequence* seq = Sequence::create(DelayTime::create(0.5f), fadeOut, callE, nullptr);

	this->runAction(seq);
	this->scheduleUpdate();
	return true;
}

void PointLabel::erase()
{
	this->removeFromParent();
}

void PointLabel::update(float delta)
{
	if (bonusColor)
	{
		colorCount--;
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<int> colorNum(100, 255);

		if (colorCount <= 0)
		{
			this->setColor(Color3B(colorNum(mt), colorNum(mt), colorNum(mt)));
			colorCount = 3;
		}
	}

	this->setPositionY(this->getPositionY() + 1.0f);
}