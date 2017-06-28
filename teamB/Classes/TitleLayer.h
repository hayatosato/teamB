#ifndef __TITLE_LAYER_H__
#define __TITLE_LAYER_H__

#include "cocos2d.h"
#include "TitleTap.h"
#include "TextNavi.h"
USING_NS_CC;

class TitleLayer : public Layer
{
public:
	CREATE_FUNC(TitleLayer);

	TitleTap* titleTap;
	Sprite*   subTitle;
	Sprite*   title;

	bool init();

	
private:
	Sprite* back;
	TextNavi* textNavi;

};
#endif