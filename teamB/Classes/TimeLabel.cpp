#include "TimeLabel.h"

bool TimeLabel::init()
{
	if (!Label::init()) return false;
	seconds = 0;
	minute =  0;

	this->initWithTTF("1", "fonts/Jiyucho.ttf", 80);
	timeStr = String::createWithFormat("%02d:%02d", minute, seconds);
	this->setString(timeStr->getCString());
	this->setColor(Color3B::BLACK);

	return true;
}

void TimeLabel::upTime(float delta)
{
	seconds++;
	if (seconds == 60)
	{
		seconds = 0;
		minute++;
	}
	timeStr = String::createWithFormat("%02d:%02d", minute, seconds);
	this->setString(timeStr->getCString());
}

//カウントアップ開始
void TimeLabel::masterTime()
{
	this->schedule(schedule_selector(TimeLabel::upTime), 1.0f);
}

//カウントアップ停止
void TimeLabel::stopTime()
{
	this->unschedule(schedule_selector(TimeLabel::upTime));
}