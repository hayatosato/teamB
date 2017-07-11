#ifndef __POINT_LABEL_H__
#define __POINT_LABEL_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class PointLabel : public Label
{
public:
	CREATE_FUNC(PointLabel);

	bool init();
	int colorCount;
	bool bonusColor;
	void update(float delta);

private:
	void erase();
};
#endif