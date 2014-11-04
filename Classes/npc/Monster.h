#ifndef __Monster_H__
#define __Monster_H__

#include "cocos2d.h"
#include "npc/Npc.h"
USING_NS_CC;

class Monster : public Npc {
public:
	Monster();
	~Monster();

	static Monster* create(NpcType type);
	bool init();
	bool onTouch(Touch* touch, Event* event);
};

#endif