#include "Knob.h"

bool Knob::init()
{
	if (!Sprite::init()) return true;

	this->initWithFile("Knob.png");

	return true;
}