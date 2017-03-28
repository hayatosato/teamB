#include "RedClock.h"

bool RedClock::init()
{
	if (!Sprite::init()) return false;

	initWithFile("RedClock.png");

	return true;
}