#include "GameScene.h"
#include "MultiResolution.h"


bool GameScene::init()
{
	if (!Scene::init()) return false;

	//WatchLayer
	_watchLayer = WatchLayer::create();
	this->addChild(_watchLayer);

	return true;
}