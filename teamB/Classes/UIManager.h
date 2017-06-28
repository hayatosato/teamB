#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class UIManager : public Node
{
public:
	static UIManager *create(int breakNum,int breakNumMax);

	bool init(int breakNum, int breakNumMax);

	void breakChangeGauge(float nowRatio,float ratioMax); //���Q�[�W�̕ω�
	
private:
	Vec2 breakNumBasePos;          //��ꂽ������\��UI�̊�ʒu
	Sprite* gaugeOne;              //���Q�[�W���n
	Sprite* breakMeter;            //���Q�[�W���[�^�[
	Sprite* gaugeTwo;              //���Q�[�W�g
	Label*  breakLabel;            //���\��

};
#endif