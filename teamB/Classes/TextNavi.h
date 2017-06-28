#ifndef __TEXT_NAVI_H__
#define __TEXT_NAVI_H__

#include "cocos2d.h"
USING_NS_CC;

class TextNavi : public Sprite
{
public:
	CREATE_FUNC(TextNavi);

	int opacity;           //透明度
	int opacitySpeed;      //フェードスピード

	bool init();

	bool textOpacity;

	void update(float delta);
	
private:

};
#endif // !__TEXT_NAVI_H__