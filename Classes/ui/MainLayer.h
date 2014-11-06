#ifndef __MainLayer_H__
#define __MainLayer_H__

#include "cocos2d.h"
#include "npc/Player.h"
#include "npc/Monster.h"
#include "npc/Boss.h"

USING_NS_CC;

class MainLayer : public Layer
{
public:	
    bool init();
	void addUI();
	bool onTouchBegan(Touch* touch, Event* event);	
	void toggleDebug(Ref* pSender);
	void addRoles();
	void addListener();
	void onTouchPause(Ref* sender);
	void update(float dt);
	bool onContactBegin(const PhysicsContact& contact);
	void onContactSeperate(const PhysicsContact& contact);
	void setPhysicsWorld(PhysicsWorld* physicsWorld){_world=physicsWorld;}

	void enemyMove(float t);
	CREATE_FUNC(MainLayer);

private:
	Player* _player;
	Monster* _monster;
	Boss* _boss;
	EventListenerTouchOneByOne* _listener_touch;
	EventListenerPhysicsContact* _listener_contact;
	PhysicsWorld* _world;
};

#endif 