#include "Knob.h"

bool Knob::init()
{
	if (!Sprite::init()) return true;

	initWithFile("newKnob.png");

	return true;
}