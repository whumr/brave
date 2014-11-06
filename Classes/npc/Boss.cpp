#include "npc/Boss.h"

Boss::Boss(){}
Boss::~Boss(){}

bool Boss::init()
{
	_initFrame = "df1-1-1.png";
	_name = "df1";
	_type = NpcType::BOSS;
	_speed = 100;
	_hp = 100;
	_maxHp =100;
	_damage = 40;
	_alarmRange = 100;
	_attackDelay = 2;

	_animationNum = 4;
	int animationFrameNum[5] ={1, 5, 4, 2, 0};
	_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);

	std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
	_animationNames.assign(animationNames, animationNames + 5);

	this->initWithSpriteFrameName(_initFrame);
	//load animation
	this->addAnimation();

	//set contact
	auto body = PhysicsBody::createBox(Size(140, 40), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(40, 0));
	body->setCategoryBitmask(ColliderType::ColliderTypeMonster);
	body->setCollisionBitmask(ColliderType::ColliderTypeNone);
	body->setContactTestBitmask(ColliderType::ColliderTypePlayer);
	this->setPhysicsBody(body); 

	this->showProgress();
//	_listener = EventListenerTouchOneByOne::create();
//	_listener->setSwallowTouches(true);
//	_listener->onTouchBegan = CC_CALLBACK_2(Boss::onTouch,this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,this);
	return true;
}

bool Boss::onTouch(Touch* touch, Event* event)
{
	return true;
}