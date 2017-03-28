#include "CenterObject.h"

bool CenterObject::init()
{
	if (!Sprite::init()) return false;

	initWithFile("CenterPoint.png");

	return true;
}