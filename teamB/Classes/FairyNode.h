#ifndef __FAIRY_NODE_H__
#define __FAIRY_NODE_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class FairyNode : public Node
{
public:
	static FairyNode *create(Vec2 enemyPos);

	Enemy* enemy;

	bool init(Vec2 enemyPos);
	void update(float delta);
	
private:

};
#endif