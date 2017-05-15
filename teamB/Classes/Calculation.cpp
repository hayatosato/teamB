#include "Calculation.h"

float Calculation::angle(Vec2 s,Vec2 e)
{
	float k = atan2(e.x - s.x, e.y - s.y);
	k = k*(180 / M_PI);
	return k;
}