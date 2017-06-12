#include "TitleScene.h"

bool TitleScene::init()
{
	if (!Scene::init()) return false;

	titleLayer = TitleLayer::create();
	this->addChild(titleLayer);

	return true;
}