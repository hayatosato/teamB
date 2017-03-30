#include "Knob.h"

bool Knob::init()
{
	if (!Sprite::init()) return true;

	initWithFile("Knob.png");

	return true;
}