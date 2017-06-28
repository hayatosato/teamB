#include "TitleLayer.h"
#include "MultiResolution.h"

bool TitleLayer::init()
{
	if (!Layer::init()) return false;
	back = Sprite::create("TitleScene/backShop.png");
	back->setPosition(designResolutionSize*0.5f);
	this->addChild(back);

	titleTap = TitleTap::create();
	this->addChild(titleTap,0);

	subTitle = Sprite::create("TitleScene/tokeikoubou.png");
	subTitle->setPosition(designResolutionSize.width*0.25f, designResolutionSize.height*0.9f);
	subTitle->setScale(0.4f);
	this->addChild(subTitle, 1);

	title = Sprite::create("TitleScene/ferock.png");
	title->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.8f);
	title->setScale(0.8f);
	this->addChild(title, 1);

	textNavi = TextNavi::create();
	textNavi->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.15f);
	textNavi->setScale(0.5f);
	this->addChild(textNavi, 1);

	return true;
}