#include "BlueClock.h"

bool BlueClock::init()
{
	if (!Sprite::init()) return false;

	initWithFile("BlueClock.png");

	return true;
}