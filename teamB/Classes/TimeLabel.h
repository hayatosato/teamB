#ifndef __TIME_LABEL_H__
#define __TIME_LABEL_H__

#include "cocos2d.h"
USING_NS_CC;

class TimeLabel : public Label
{
public:
	CREATE_FUNC(TimeLabel);

	bool init();
	
	int seconds;       //秒
	int minute;        //分

	String* timeStr;
	void masterTime();              //呼ぶとカウントアップを始める
	void stopTime();                //カウントアップを終わる
private:
	void upTime(float delta);


};
#endif