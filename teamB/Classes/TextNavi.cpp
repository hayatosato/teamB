#include "TextNavi.h"

bool TextNavi::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithFile("TitleScene/tap.png");
	opacitySpeed = 5;
	textOpacity = true;
	opacity = 255;

	this->scheduleUpdate();
	return true;
}

void TextNavi::update(float delta)
{
	if (textOpacity)
	{
		opacity -= opacitySpeed;
		if (opacity <= 0)
		{
			textOpacity = false;
		}
	}
	else
	{
		opacity += opacitySpeed;
		if (opacity >= 255)
		{
			textOpacity = true;
		}
	}
	this->setOpacity(opacity);
}