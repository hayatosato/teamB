#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include "cocos2d.h"
USING_NS_CC;

class Calculation
{
public:
	static float angle(Vec2 s, Vec2 e);                           //�p�x��Ԃ�(�n�_,�I�_)
	static Vec2  sen(Vec2 s, Vec2 e, float t);                    //���`���(�n�_,�I�_,����)
	static Vec2 setPos(Vec2 createPos, float length, float deg);  //��_�ɑ΂��Ē����Ɗp�x����ʒu�����߂Ĕz�u����(��_�A�����A�p�x)
	static float sq(Vec2 goal, Vec2 my);                          //2�_�Ԃ̋��������߂�(��_,���g�̈ʒu)
	
private:

};
#endif