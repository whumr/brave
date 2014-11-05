#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "npc/Npc.h"
USING_NS_CC;

class Player : public Npc {
public:
	Player();
	~Player();

	bool init();
	bool onTouch(Touch* touch, Event* event);

	//void attack();

	CREATE_FUNC(Player);
};
#endif