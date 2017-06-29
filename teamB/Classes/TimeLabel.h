#ifndef __TIME_LABEL_H__
#define __TIME_LABEL_H__

#include "cocos2d.h"
USING_NS_CC;

class TimeLabel : public Label
{
public:
	CREATE_FUNC(TimeLabel);

	bool init();
	
	int seconds;       //�b
	int minute;        //��

	String* timeStr;
	void masterTime();              //�ĂԂƃJ�E���g�A�b�v���n�߂�
	void stopTime();                //�J�E���g�A�b�v���I���
private:
	void upTime(float delta);


};
#endif