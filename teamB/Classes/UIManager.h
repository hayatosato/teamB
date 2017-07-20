#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class UIManager : public Node
{
public:
	CREATE_FUNC(UIManager);

	bool init();
	int score;
	
	void update(float delta);

private:
	Vec2 scoreBasePos;          //壊れた数字を表すUIの基準位置
	Sprite* gauge;              //壊れゲージ下地
	Sprite* scoreBoard;         //スコア板
	Label*  scoreLabel;         //壊れ表示


};
#endif