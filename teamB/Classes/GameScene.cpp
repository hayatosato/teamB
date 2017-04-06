#include "GameScene.h"
<<<<<<< HEAD
#include "MultiResolution.h"
=======
>>>>>>> 4fd1ba1ef1549ef0a3e53f28073be19d237a49df

bool GameScene::init()
{
	if (!Scene::init()) return false;

	//WatchLayer
	_watchLayer = WatchLayer::create();
	this->addChild(_watchLayer);

	return true;
}