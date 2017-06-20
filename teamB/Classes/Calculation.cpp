#include "Calculation.h"

//角度
float Calculation::angle(Vec2 s,Vec2 e)
{
	float k = atan2(e.x - s.x, e.y - s.y);
	k = k*(180 / M_PI);
	return k;
}

//線形補間座標
Vec2 Calculation::sen(Vec2 s, Vec2 e, float t)
{
	return (1 - t) * s + t * e;
}

//線形補間float
float Calculation::senF(float s,float e,float t)
{
	return (1.0f - t) * s + t * e;
}

//基準点に対して長さと角度から位置を求めて配置する(基準点、長さ、角度)
Vec2 Calculation::setPos(Vec2 createPos, float length, float deg)
{
	//処理するためにデグリーをラジアンに直す
	float Rad = deg * M_PI / 180;

	//角度と長さから配置位置のXとYを求める
	float Y = sin(Rad) * length;
	float X = cos(Rad) * length;

	//基準点(今回なら時計の中心)からの配置位置に直す
	Vec2 vec = createPos + Vec2(X, Y);

	//配置位置をリターンで返す。この値をsetPostionするだけ！
	return vec;
}

//2点間の距離を求める(基準点,自身の位置)
float Calculation::sq(Vec2 goal, Vec2 my)
{
	float a = sqrt((my.x - goal.x)*(my.x - goal.x) + (my.y - goal.y)*(my.y - goal.y));

	return a;
}