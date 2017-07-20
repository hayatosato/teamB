#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class UIManager : public Node
{
public:
	CREATE_FUNC(UIManager);

	bool init();
	int score;
	
	void update(float delta);

private:
	Vec2 scoreBasePos;          //��ꂽ������\��UI�̊�ʒu
	Sprite* gauge;              //���Q�[�W���n
	Sprite* scoreBoard;         //�X�R�A��
	Label*  scoreLabel;         //���\��


};
#endif