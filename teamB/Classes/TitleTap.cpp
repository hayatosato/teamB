#include "TitleTap.h"
#include "GameScene.h"

bool TitleTap::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	// �^�b�`�C�x���g��L���ɂ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleTap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TitleTap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleTap::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
}

//�^�b�v������
bool TitleTap::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, GameScene::create(), Color3B::BLACK));
	return true;
}

//�^�b�v��
void TitleTap::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

//�^�b�v��߂��Ƃ�
void TitleTap::onTouchEnded(Touch* pTouch, Event* pEvent)
{
}