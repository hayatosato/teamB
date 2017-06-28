#ifndef __TITLE_H__
#define __TITLE_H__

#include "cocos2d.h"
USING_NS_CC;

class Title : public Sprite
{
public:
	CREATE_FUNC(Title);

	bool init();

	bool titleGravity;  //重力
	void upStart();     //動きの始まり
	
private:
	float speed;
	void delayWatchStart(float delta);      //カウントダウンを始める
	void update(float delta);

};
#endif