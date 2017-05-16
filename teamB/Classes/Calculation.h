#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include "cocos2d.h"
USING_NS_CC;

class Calculation
{
public:
	static float angle(Vec2 s, Vec2 e);                           //角度を返す(始点,終点)
	static Vec2  sen(Vec2 s, Vec2 e, float t);                    //線形補間(始点,終点,割合)
	static Vec2 setPos(Vec2 createPos, float length, float deg);  //基準点に対して長さと角度から位置を求めて配置する(基準点、長さ、角度)
	static float sq(Vec2 goal, Vec2 my);                          //2点間の距離を求める(基準点,自身の位置)
	
private:

};
#endif