#include "Clear.h"
#include "MultiResolution.h"

bool Clear::init()
{
	if (!Node::init()) return false;

	clear = Sprite::create("GameScene/clear.png");
	this->addChild(clear,3);

	fairyOne = EffectFairy::create();
	fairyOne->setScale(0.4f);
	fairyOne->setPosition(clear->getPosition().x + 150, clear->getPosition().y + 100);
	fairyOne->setRotation(15);
	this->addChild(fairyOne,1);

	fairyTwo = EffectFairy::create();
	fairyTwo->setScale(0.4f);
	fairyTwo->setPosition(clear->getPosition().x - 150, clear->getPosition().y + 100);
	fairyTwo->setRotation(-15);
	this->addChild(fairyTwo, 1);



	return true;
}