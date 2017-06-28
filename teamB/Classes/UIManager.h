#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class UIManager : public Node
{
public:
	static UIManager *create(int breakNum,int breakNumMax);

	bool init(int breakNum, int breakNumMax);

	void breakChangeGauge(float nowRatio,float ratioMax); //壊れゲージの変化
	
private:
	Vec2 breakNumBasePos;          //壊れた数字を表すUIの基準位置
	Sprite* gaugeOne;              //壊れゲージ下地
	Sprite* breakMeter;            //壊れゲージメーター
	Sprite* gaugeTwo;              //壊れゲージ枠
	Label*  breakLabel;            //壊れ表示

};
#endif