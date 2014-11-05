#ifndef __Npc_H__
#define __Npc_H__

#include "cocos2d.h"
USING_NS_CC;

class Npc : public Sprite {
public:
	enum NpcType{
		PLAYER,
		MONSTER1,
		MONSTER2,
		BOSS
	};

	enum AnimationType{
		WALKING = 0,
		ATTACKING,
		DEAD,
		BEINGHIT,
		SKILL
	};

	enum ColliderType {  
		ColliderTypeNone			= 0x0,
		ColliderTypePlayer			= 0x1,  
		ColliderTypeMonster		    = 0x1<<1,  
		ColliderTypeBOSS	        = 0x1<<2  
	}; 

	Npc();
	~Npc();

	void addAnimation();
	Animate* getAnimateByType(AnimationType type);
	void playAnimationForever(AnimationType type);
	void stop();

	void walkTo(Vec2 dest);
	void idle();	
	void attack();
	void die();

	void addTarget(Npc* target);
	void removeTarget(Npc* target);
	void beAttacked(Npc* empty);
	Npc* checkTarget();

	virtual bool onTouch(Touch* touch, Event* event);

	CC_SYNTHESIZE(int, _hp, Hp);
	CC_SYNTHESIZE(int, _maxHp, MaxHp);
	CC_SYNTHESIZE(int, _damage, Damage);
	CC_SYNTHESIZE(NpcType, _type, Type);

protected:
	std::string _initFrame;
	int _animationNum; 
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;
	float _speed;
	Vector<Npc*> _targets;
};

#endif