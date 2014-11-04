#ifndef __Boss_H__
#define __Boss_H__

#include "cocos2d.h"
#include "npc/Npc.h"
USING_NS_CC;

class Boss : public Npc {
public:
	Boss();
	~Boss();

	bool init();
	bool onTouch(Touch* touch, Event* event);

	CREATE_FUNC(Boss);
};

#endif