#include "Calculation.h"

//�p�x
float Calculation::angle(Vec2 s,Vec2 e)
{
	float k = atan2(e.x - s.x, e.y - s.y);
	k = k*(180 / M_PI);
	return k;
}

//���`��ԍ��W
Vec2 Calculation::sen(Vec2 s, Vec2 e, float t)
{
	return (1 - t) * s + t * e;
}

//���`���float
float Calculation::senF(float s,float e,float t)
{
	return (1.0f - t) * s + t * e;
}

//��_�ɑ΂��Ē����Ɗp�x����ʒu�����߂Ĕz�u����(��_�A�����A�p�x)
Vec2 Calculation::setPos(Vec2 createPos, float length, float deg)
{
	//�������邽�߂Ƀf�O���[�����W�A���ɒ���
	float Rad = deg * M_PI / 180;

	//�p�x�ƒ�������z�u�ʒu��X��Y�����߂�
	float Y = sin(Rad) * length;
	float X = cos(Rad) * length;

	//��_(����Ȃ玞�v�̒��S)����̔z�u�ʒu�ɒ���
	Vec2 vec = createPos + Vec2(X, Y);

	//�z�u�ʒu�����^�[���ŕԂ��B���̒l��setPostion���邾���I
	return vec;
}

//2�_�Ԃ̋��������߂�(��_,���g�̈ʒu)
float Calculation::sq(Vec2 goal, Vec2 my)
{
	float a = sqrt((my.x - goal.x)*(my.x - goal.x) + (my.y - goal.y)*(my.y - goal.y));

	return a;
}