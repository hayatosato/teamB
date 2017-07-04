#ifndef __CLEAR_TEXT_H__
#define __CLEAR_TEXT_H__

#include "cocos2d.h"
USING_NS_CC;

class ClearText : public Node
{
public:
	static ClearText *create(int nowM,int nowS,int highM,int highS,bool highScoreC);

	bool init(int nowM, int nowS, int highM, int highS, bool highScoreC);
	
	Label* nowScore;
	Label* highScore;
	
private:

};
#endif