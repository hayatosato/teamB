#ifndef __TITLE_H__
#define __TITLE_H__

#include "cocos2d.h"
USING_NS_CC;

class Title : public Sprite
{
public:
	CREATE_FUNC(Title);

	bool init();

	bool titleGravity;  //�d��
	void upStart();     //�����̎n�܂�
	
private:
	float speed;
	void delayWatchStart(float delta);      //�J�E���g�_�E�����n�߂�
	void update(float delta);

};
#endif