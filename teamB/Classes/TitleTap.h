#ifndef __TITLE_TAP_H__
#define __TITLE_TAP_H__

#include "cocos2d.h"
USING_NS_CC;

class TitleTap : public Sprite
{
public:
	CREATE_FUNC(TitleTap);

	bool init();
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	
private:

};
#endif